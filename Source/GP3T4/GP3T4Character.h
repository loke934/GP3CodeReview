// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IsPlayerCharacter.h"
#include "Interactables/T4Interactable.h"
#include "GP3T4Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class AT4Meteorite;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRightClick);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRespawn);

UCLASS(config=Game)
class AGP3T4Character : public ACharacter, public IIsPlayerCharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	AGP3T4Character();

protected:
	virtual void BeginPlay();
	void GetHitTargetUnderCursor();
	virtual void Tick(float DeltaSeconds) override;

	virtual void PostInitializeComponents() override;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float TurnRateGamepad;

	float MouseSensitivityX; //gets their value from game instance
	float MouseSensitivityY;
	
	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnUseItem OnUseItem;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnRightClick OnRightClick;

	/*Meteorite*/
	UPROPERTY()
	AT4Meteorite* MeteoriteWeapon;
	
	bool bHasWeapon = false;
	
protected:
	
	/** Fires a projectile. */
	void OnPrimaryAction();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;

	void AddYaw(const float Val);
	void AddPitch(const float Val);
	
protected:	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	void InteractWithTarget() const;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);


	/*
	 * Pause menu
	 */
	

	void OnSecondaryAction(FKey PressedKey);

public:
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
	UFUNCTION(BlueprintCallable)
    void OnPauseMenuButtonPressed();

protected:
	/*
	 * Sprinting
	 */
	void StartSprinting();
	void StopSprinting();

public:
	/*
	 * Lock rotation
	 */
	UFUNCTION(BlueprintCallable)
	void LockPlayerLookRotation(bool bLockMovement = true);

	UFUNCTION(BlueprintCallable)
	void LockInputAtSleep(const bool bLock, const FVector NewLocation, const FRotator NewRotation);

protected:
	/*
	 *  Interaction 
	 */
	UPROPERTY(EditAnywhere, Category = "Interaction")
	float InteractionLength = 500.f;

	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	UPROPERTY()
	AT4Interactable* HitTarget;
	float DistSinceLastStep;
	
	/*
	 * Sprint
	 */
	UPROPERTY(EditAnywhere, Category = "Moving")
	float BaseMovementSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Moving")
	float SprintMovementSpeed = 900.f;

	/*
	 * Camera lock
	 */
	UPROPERTY(EditAnywhere, Category = "CameraLock")
	float YawMax = 60.f;
	UPROPERTY(EditAnywhere, Category = "CameraLock")
	float YawMin = -60.f;

	UPROPERTY(EditAnywhere, Category = "CameraLock")
	float PitchMax = 60.f;
	UPROPERTY(EditAnywhere, Category = "CameraLock")
	float PitchMin = -60.f;
	
	UPROPERTY()
	bool LockCameraMovement = false;
	UPROPERTY()
	bool bDisablePlayerInput = false;
	UPROPERTY()
	APlayerCameraManager* CameraManger;

	/*
	* Pickup and Look at objects
	*/
	UPROPERTY(VisibleAnywhere)
	class UPickUpAndLookAtComponent* PickUpAndLookAtComponent;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* PositionToHoldItem;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshToInspect;

	bool bMouseButtonDown = false;

	UPROPERTY(EditAnywhere)
	float HeldItemRotationSpeed = 100.f;

protected:
	void AdjustHeldObjectYaw(float Val);
	void AdjustHeldObjectPitch(float Val);
	void OnPrimaryActionStopped();	

public:
	FORCEINLINE UPickUpAndLookAtComponent* GetPickUpAndLookAtComponent(){return PickUpAndLookAtComponent;} 
	FORCEINLINE FVector GetPickUpAndLookAtLocation(){return PositionToHoldItem->GetComponentLocation();}
	FORCEINLINE FRotator GetPlayerViewpointRotation(){return PlayerViewpointRotation;}

	void SetMeshToInspect(class UStaticMesh* MeshToHold, float Scale, float ZOffset);
	void DisablePlayerMovement(bool bShouldDisable);

	UPROPERTY(BlueprintAssignable, Category = "Respawn")
	FOnRespawn OnRespawn;

	UFUNCTION(BlueprintCallable)
	void PlayerRespawn();

	
};

