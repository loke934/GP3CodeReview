// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GP3T4/Interfaces/T4IsOverlapping.h"
#include "T4TriggerBase.generated.h"



USTRUCT()
struct FActorInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	AActor* TargetActor;

	UPROPERTY(EditAnywhere)
	bool bIsSingleUse;

	UPROPERTY()
	bool bHasBeenUsed;
	
};


UCLASS()
class GP3T4_API AT4TriggerBase : public AActor, public IT4IsOverlapping
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AT4TriggerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	virtual void TriggerEffect();

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere)
	TArray<FActorInfo> Actors;

public:
	virtual void OnOverlapTriggered_Implementation() override;
};
