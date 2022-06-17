#pragma once
#include "GameFramework/Actor.h"
#include "T4StretchyCorridor.generated.h"

UCLASS(Abstract)
class GP3T4_API AT4StretchyCorridor : public AActor
{
	GENERATED_BODY()
	
public:	
	AT4StretchyCorridor();

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsPlayerInside();


	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnTick"))
	void OnReceiveTick();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnBeginPlay"))
	void OnReceiveBeginPlay();
	
private:
	void SetBackWallPosition();
	
public:
	UPROPERTY(BlueprintReadOnly)
	FVector BackWallPosition;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bRotatedForward;
	
private:
	UPROPERTY()
	ACharacter* Player;

	FVector StretchyLocation;
	FVector StretchyRight;
	const float MulWithSqrt = 100.f;
	const float MinDist = 200.f;
	const float MaxDist = 10000.f;

};
