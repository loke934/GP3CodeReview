// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T4AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "T4AIBaseCharacter.generated.h"

class ATargetPoint;
UCLASS()
class GP3T4_API AT4AIBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AT4AIBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetNewMaterial(UStaticMeshComponent* ActorMesh, int MaterialSlot, UMaterialInterface* Material);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Settings")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Material")
	UMaterialInterface* WindowMaterial;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Material")
	UMaterialInterface* AlertWindowMaterial;

	UPROPERTY(EditAnywhere, Category = "AI Material")
	int AlertMaterialSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI Material")
	bool bShouldChangeMaterial;
	
	UPROPERTY(EditAnywhere, Category = "AI Settings")
	float NewMovementSpeed;

	UPROPERTY()
	FVector StartPos;

	UPROPERTY()
	FRotator StartRot;

	UPROPERTY()
	AT4AIController* ControllerOwner;

public:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// What happens when player is seen
	UFUNCTION(BlueprintImplementableEvent)
	void OnNoticedPlayer();

	// Sets the position and rotation to start values
	UFUNCTION(BlueprintCallable)
	void MoveToStart();

	UPROPERTY()
	bool bHasSeenPlayer;

	UPROPERTY(EditAnywhere, Category = "AI BT Behavior")
	UBehaviorTree* PawnBehaviorTree;
	
	UPROPERTY(EditInstanceOnly, Category = "AI BT Behavior")
	TArray<ATargetPoint*> FollowPoints;
	
};
