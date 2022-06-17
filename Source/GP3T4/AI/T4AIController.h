// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionTypes.h"
#include "T4AIController.generated.h"


class AT4AIBaseCharacter;
class UAISenseConfig_Sight;

UCLASS()
class GP3T4_API AT4AIController final : public AAIController
{
	GENERATED_BODY()

public:
	
	AT4AIController();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	void InitializePawnSettings();
	
	UPROPERTY(BlueprintReadWrite)
	UAISenseConfig_Sight* Sight;

	UPROPERTY(BlueprintReadOnly)
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly ,Category = "AI Settings")
	UBehaviorTree* DefaultBehaviorToUse;

	UPROPERTY()
	AT4AIBaseCharacter* ControlledPawn;

	UPROPERTY(VisibleAnywhere)
	bool bIsGoingReverse;

	UPROPERTY()
	bool bIsFirstFollowPoint;

	UPROPERTY()
	int TargetIndex;

public:

	UFUNCTION()
	FVector GetNextPoint();
	
};
