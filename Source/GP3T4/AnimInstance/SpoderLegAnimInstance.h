#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SpoderLegAnimInstance.generated.h"


UCLASS()
class GP3T4_API USpoderLegAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/*
	 * Sounds
	 */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnFootstepCompleted"))
	void PlayFootstepSound();

private:	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class AT4ProceduralLeg* LegComponent;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector LegPosition;

	UPROPERTY()
	USceneComponent* TargetPosition;
	bool bIsLerpingPosition = false;
	FVector MoveToPosition;	
	FVector LastValidPosition;

	/*
	 * For zig-zag
	 */	
	bool bIsGrounded = false;
	bool bCanMove = false;
	bool bLegOnWall = false;
	float LerpProgress = 0.f;	

private:
	void SetIsGrounded();
};
