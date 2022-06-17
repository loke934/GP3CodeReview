#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T4ProceduralLeg.generated.h"

UCLASS()
class GP3T4_API AT4ProceduralLeg : public AActor
{
	GENERATED_BODY()
	
public:	
	AT4ProceduralLeg();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* LegSkeletalMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* LegPosComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* LegTargetComponent;	

	UPROPERTY()
	AT4ProceduralLeg* OppositeLeg;

	bool bIsGrounded = false;

	UPROPERTY(EditAnywhere)
	bool bIsFrontLeg = false;

	/*
	 * Movement properties
	 */
	UPROPERTY(EditAnywhere)
	float DistanceBeforeTakingNextStep = 180.f;
	UPROPERTY(EditAnywhere)
	float LegMovementInterpSpeed = 1400.f;
	UPROPERTY(EditAnywhere)
	float FrontLegOffsetToBody = 25.f;
	UPROPERTY(EditAnywhere)
	float FrontLegOffsetForward = 75.f;
	UPROPERTY(EditAnywhere)/*Minimum amount of milliseconds we should wait until we are allowed to move a specific leg*/
	float MinGroundedTime = 0.07f;
	UPROPERTY(EditAnywhere) /*Max distance to target location before saying that we are close enough to be grounded*/
	float CutoffDistanceBeforeBeingGrounded = 30.f;
	UPROPERTY(EditAnywhere)
	class UCurveFloat* LegZCurve;
};
