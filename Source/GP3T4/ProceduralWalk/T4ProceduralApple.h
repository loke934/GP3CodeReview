#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T4ProceduralApple.generated.h"

UCLASS()
class GP3T4_API AT4ProceduralApple : public AActor
{
	GENERATED_BODY()
	
public:	
	AT4ProceduralApple();
	void SetupSpiderLegs();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	/*Aggro handled entirely from blueprint*/
	UFUNCTION(BlueprintCallable)
	void StartAggro();

	UFUNCTION(BlueprintCallable)
	void StopAggro(FVector PlayerLocation, FVector Location);

protected:
	/*
	 * Apple
	 */
	UPROPERTY(EditAnywhere, Category= "Apple")
	UStaticMeshComponent* AppleMesh;

	UPROPERTY()
	ACharacter* Player;

	UPROPERTY(EditAnywhere, Category= "Apple")
	float MinDistFromPlayer = 300.f;
	
	UPROPERTY(EditAnywhere, Category= "Apple")
	float FollowSpeed = 375.f;

	UPROPERTY()
	bool bShouldFollowPlayer = false;

	UPROPERTY(EditAnywhere)
	bool bAtMinDistance;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnStartMoving"))
	void ReceiveStartMoving();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnSTopMoving"))
	void ReceiveStopMoving();
	
	public:
	/*
	 * Legs (Should probably move these badbois to a component)
	 */
	UPROPERTY()
	class USceneComponent* LegsParent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AT4ProceduralLeg> LegBP;

	UPROPERTY(EditAnywhere)
	class UChildActorComponent* FrontLeftLeg;

	UPROPERTY(EditAnywhere)
	class UChildActorComponent* FrontRightLeg;

	UPROPERTY(EditAnywhere)
	class UChildActorComponent* BackLeftLeg;

	UPROPERTY(EditAnywhere)
	class UChildActorComponent* BackRightLeg;

	UPROPERTY(EditAnywhere)/*Add child scene components for each leg you want to create*/
	class USceneComponent* LegPositions;

	UPROPERTY()
	class AT4ProceduralLeg* FrontLeftLegCast;
	UPROPERTY()
	class AT4ProceduralLeg* FrontRightLegCast;
	UPROPERTY()
	class AT4ProceduralLeg* BackLeftLegCast;
	UPROPERTY()
	class AT4ProceduralLeg* BackRightLegCast;

};
