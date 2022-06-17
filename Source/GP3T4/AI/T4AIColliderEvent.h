// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T4AIBaseCharacter.h"
#include "GameFramework/Actor.h"
#include "T4AIColliderEvent.generated.h"

class UBoxComponent;
UCLASS()
class GP3T4_API AT4AIColliderEvent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AT4AIColliderEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndOverlap( UPrimitiveComponent* OverlappedComp,  AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, Category = "AI Search")
	TSubclassOf<AT4AIBaseCharacter> AIClass;

	UPROPERTY(EditAnywhere, Category = "AI Overlap Event")
	FName TriggerName;

	UPROPERTY(EditAnywhere, Category = "AI Overlap Event")
	bool bBoolValue;


public:	

};
