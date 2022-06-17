// Fill out your copyright notice in the Description page of Project Settings.


#include "T4AIBaseCharacter.h"
#include "T4AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GP3T4/GP3T4Character.h"

// Sets default values
AT4AIBaseCharacter::AT4AIBaseCharacter()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AI Mesh"));
	MeshComponent->SetupAttachment(GetRootComponent());
	
	bUseControllerRotationYaw = false;
	bShouldChangeMaterial = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate.Yaw = 180;
}

// Called when the game starts or when spawned
void AT4AIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	ControllerOwner = Cast<AT4AIController>(GetController());
	AGP3T4Character* Player = Cast<AGP3T4Character>(GetWorld()->GetFirstPlayerController());
	if(Player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Found player");
		Player->OnRespawn.AddDynamic(this, &AT4AIBaseCharacter::MoveToStart);	
	}
	StartPos = GetActorLocation();
	StartRot = GetActorRotation();

	if(NewMovementSpeed > 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = NewMovementSpeed;
	}
}

void AT4AIBaseCharacter::SetNewMaterial(UStaticMeshComponent* ActorMesh, int MaterialSlot, UMaterialInterface* Material)
{
	if(Material && ActorMesh)
	{
		ActorMesh->SetMaterial(MaterialSlot,Material);
	}
}

// Called to bind functionality to input
void AT4AIBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
 // Sets AI back to start and loses sight of player
void AT4AIBaseCharacter::MoveToStart()
{
	SetActorLocation(StartPos);
	SetActorRotation(StartRot);

	if(ControllerOwner)
	{
		bHasSeenPlayer = false;
		ControllerOwner->GetBlackboardComponent()->SetValueAsObject("Player", nullptr);
		ControllerOwner->GetBlackboardComponent()->SetValueAsBool("bHasSeenPlayer", false);
		if(WindowMaterial && MeshComponent->GetNumMaterials() >= AlertMaterialSlot)
		{
			SetNewMaterial(MeshComponent, AlertMaterialSlot, WindowMaterial);	
		}
	}
}

