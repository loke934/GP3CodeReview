// Copyright Epic Games, Inc. All Rights Reserved.

#include "GP3T4Character.h"
#include "GP3T4Projectile.h"
#include "T4GameInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"
#include "HUD/T4PlayerHUD.h"
#include "Interfaces/IsInteractable.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerComponents/PickUpAndLookAtComponent.h"
#include "Interactables/T4Meteorite.h"
#include "Kismet/KismetMathLibrary.h"


//////////////////////////////////////////////////////////////////////////
// AGP3T4Character

AGP3T4Character::AGP3T4Character()
{
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	 //Movement speed	
	GetCharacterMovement()->MaxWalkSpeed = BaseMovementSpeed;
	
	//Pickup & Look at component 
	PickUpAndLookAtComponent = CreateDefaultSubobject<UPickUpAndLookAtComponent>(TEXT("PickUpAndLookAtComponent"));

	PositionToHoldItem = CreateDefaultSubobject<USceneComponent>(TEXT("PositionToHoldInspectedItem"));
	PositionToHoldItem->SetupAttachment(FirstPersonCameraComponent);
	MeshToInspect = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshToInspect"));
	MeshToInspect->SetupAttachment(PositionToHoldItem);    	
}

void AGP3T4Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	bHasWeapon = false;
	const UT4GameInstance* GameInst = UT4GameInstance::Get(this);
	MouseSensitivityX = GameInst->SensitivityX;
	MouseSensitivityY = GameInst->SensitivityY;
	if (GameInst->InvertAxies)
	{
		TurnRateGamepad *= -1;
		MouseSensitivityX *= -1;
		MouseSensitivityY *= -1;
	}
}

void AGP3T4Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Get the actor we're currently aiming at (if close enough)
	GetHitTargetUnderCursor();
}

void AGP3T4Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PickUpAndLookAtComponent->Character = this;
}

//////////////////////////////////////////////////////////////////////////// Input

void AGP3T4Character::AddYaw(const float Val)
{
	AddControllerYawInput(MouseSensitivityX * Val);
}

void AGP3T4Character::AddPitch(const float Val)
{
	AddControllerPitchInput(MouseSensitivityY * Val);
}

void AGP3T4Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Bind sprint event
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AGP3T4Character::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AGP3T4Character::StopSprinting);

	// Bind secondary action (Mouse 2 / Right click) | Has to be above primary action for now
	PlayerInputComponent->BindAction("SecondaryAction", IE_Pressed, this, &AGP3T4Character::OnSecondaryAction);
	
	// Bind fire event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AGP3T4Character::OnPrimaryAction);
	PlayerInputComponent->BindAction("PrimaryAction", IE_Released, this, &AGP3T4Character::OnPrimaryActionStopped);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AGP3T4Character::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AGP3T4Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &AGP3T4Character::AddYaw);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &AGP3T4Character::AddPitch);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AGP3T4Character::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AGP3T4Character::LookUpAtRate);

	//Open the pause menu when in game
	PlayerInputComponent->BindAction(
		"PauseMenu", EInputEvent::IE_Pressed, this, &AGP3T4Character::OnPauseMenuButtonPressed).bExecuteWhenPaused = true;

	//Spin mesh that is held
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &AGP3T4Character::AdjustHeldObjectYaw);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &AGP3T4Character::AdjustHeldObjectPitch);	
}

void AGP3T4Character::OnPrimaryAction()
{
	bMouseButtonDown = true;	
	if (bDisablePlayerInput) return;
	
	// Trigger the OnItemUsed Event
	OnUseItem.Broadcast();

	if (MeteoriteWeapon == nullptr) {bHasWeapon = false;}
	
	if (bHasWeapon)
	{
		MeteoriteWeapon->Shoot();
	}
	else if (PickUpAndLookAtComponent && !PickUpAndLookAtComponent->bIsInspecting){
		InteractWithTarget();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("primary")));
		}
	}
}

void AGP3T4Character::OnSecondaryAction(FKey PressedKey)
{
	if (MeshToInspect == nullptr /*|| PressedKey.GetFName() == "LeftMouseButton" */) { return;}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("Secondary")));
	}
	
	PickUpAndLookAtComponent->StopInspectingItem();
	OnRightClick.Broadcast();	
}

void AGP3T4Character::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnPrimaryAction();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AGP3T4Character::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void AGP3T4Character::MoveForward(float Value)
{
	if (bDisablePlayerInput) return;
	
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AGP3T4Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AGP3T4Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AGP3T4Character::LookUpAtRate(float Rate)
{
	if (bDisablePlayerInput) {return;}
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

bool AGP3T4Character::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AGP3T4Character::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AGP3T4Character::EndTouch);

		return true;
	}

	return false;
}

//Raycast under cursor
void AGP3T4Character::GetHitTargetUnderCursor()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewpointLocation, PlayerViewpointRotation);

	const FVector LineStart = PlayerViewpointLocation;
	const FVector LineEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * InteractionLength;

	FHitResult OutHit;
	if (!bDisablePlayerInput)
	{
		GetWorld()->LineTraceSingleByChannel(OutHit, LineStart, LineEnd, ECC_Visibility);	
	}

	const bool bHitSame = HitTarget == OutHit.GetActor();
	if (bHitSame) { return; }
	
	const bool bDeactivateOld = HitTarget != nullptr;
	if (bDeactivateOld)
	{
		HitTarget->EnableOutline(false);
		HitTarget = nullptr;
	}

	const bool bEnableNew = OutHit.GetActor() != nullptr && OutHit.GetActor()->Implements<UIsInteractable>();
	if (bEnableNew)
	{
		HitTarget = Cast<AT4Interactable>(OutHit.GetActor());
		HitTarget->EnableOutline(true);
	}
}

//Interact with target under cursor
void AGP3T4Character::InteractWithTarget() const
{
	if (HitTarget)
	{
		HitTarget->InteractWithObject();
	}
}

//Pause menu
void AGP3T4Character::OnPauseMenuButtonPressed()
{
	if (const auto World = GetWorld())
	{
		if (const auto PlayerController = World->GetFirstPlayerController())
		{
			auto PlayerHUD = Cast<AT4PlayerHUD>(PlayerController->GetHUD());
			if (PlayerHUD)
			{
				PlayerHUD->ConstructPauseMenu(PlayerController);
			}
		}
	}
}

/*
 * Start sprinting
 */
void AGP3T4Character::StartSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintMovementSpeed;
}

void AGP3T4Character::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = BaseMovementSpeed;
}

/*
 * Lock rotation
 */
void AGP3T4Character::LockPlayerLookRotation(bool bLockMovement)
{	
	CameraManger = CameraManger == nullptr ? UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0) : CameraManger;
	if (CameraManger == nullptr) {return;}

	if (bLockMovement)
	{
		const APlayerController* PlayerController = UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0);
		const float CurrYaw = PlayerController->GetControlRotation().Yaw;
		const float CurrPitch = PlayerController->GetControlRotation().Pitch;
		
		CameraManger->ViewYawMax = CurrYaw + YawMax;
		CameraManger->ViewYawMin = CurrPitch + YawMin;
		CameraManger->ViewPitchMax = CurrPitch + PitchMax;
		CameraManger->ViewPitchMin = CurrPitch + PitchMin;
	}
	else
	{
		//Reset to full view
		CameraManger->ViewYawMax = 359.99f;
		CameraManger->ViewYawMin = 0.f;
		CameraManger->ViewPitchMax = 89.99f;
		CameraManger->ViewPitchMin = -89.99f;
	}
	DisablePlayerMovement(bLockMovement);
}

void AGP3T4Character::LockInputAtSleep(const bool bLock, const FVector NewLocation, const FRotator NewRotation)
{
	GetCapsuleComponent()->SetCollisionEnabled(bLock? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0);
	PlayerController->SetControlRotation(NewRotation);
	SetActorLocation(NewLocation);
	LockPlayerLookRotation(bLock);
}

void AGP3T4Character::DisablePlayerMovement(bool bShouldDisable)
{
	bDisablePlayerInput = bShouldDisable;
	if (bShouldDisable)
	{
		GetCharacterMovement()->DisableMovement();
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}	
}

void AGP3T4Character::PlayerRespawn()
{
	OnRespawn.Broadcast();
}

void AGP3T4Character::SetMeshToInspect(UStaticMesh* MeshToHold, float Scale, float ZOffset)
{
	MeshToInspect->SetStaticMesh(MeshToHold);
	MeshToInspect->SetWorldScale3D(FVector(Scale,Scale,Scale));
	auto PositionWithOffset = MeshToInspect->GetComponentLocation();
	PositionWithOffset.Z += ZOffset;

	MeshToInspect->SetWorldLocation(PositionWithOffset);
}

//Left and right rotation
void AGP3T4Character::AdjustHeldObjectYaw(float Val)
{
	if (/*bMouseButtonDown*/ PickUpAndLookAtComponent->bIsInspecting)
	{
		auto RelRot = PositionToHoldItem->GetRelativeRotation();
		RelRot.Yaw += Val * -1.f * HeldItemRotationSpeed * GetWorld()->DeltaTimeSeconds;
		PositionToHoldItem->SetRelativeRotation(RelRot);


		/*auto ForwardVector = GetActorForwardVector();
		auto RightVector = GetActorRightVector();
		auto UpVector = GetActorUpVector();

		auto FirstRotation = ForwardVector.RotateAngleAxis(Val * -100.f, UpVector);
		auto SecondRotation = RightVector.RotateAngleAxis(Val * -100.f, UpVector);	
		
		auto RelativeRot = UKismetMathLibrary::MakeRotationFromAxes(FirstRotation, SecondRotation,UpVector);

		PositionToHoldItem->SetRelativeRotation(RelativeRot);*/
	}	
}

//Up and down rotation
void AGP3T4Character::AdjustHeldObjectPitch(float Val)
{
	if (/*bMouseButtonDown*/PickUpAndLookAtComponent->bIsInspecting) 
	{
		FRotator RelRot = FRotator::ZeroRotator;
		RelRot.Pitch += Val * HeldItemRotationSpeed * GetWorld()->DeltaTimeSeconds;

		FQuat Quat = RelRot.Quaternion();
		PositionToHoldItem->AddRelativeRotation(Quat);
	}	
}

void AGP3T4Character::OnPrimaryActionStopped()
{
	bMouseButtonDown = false;
}
