#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GP3T4/Interfaces/T4CanBeHit.h"
#include "T4Planet.generated.h"

UCLASS()
class GP3T4_API AT4Planet : public AActor, public IT4CanBeHit
{
	GENERATED_BODY()
	
public:	
	AT4Planet();
	virtual void Tick(float DeltaTime) override;
	virtual void GotHit(AActor* OtherActor) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnDestroy"))
	void ReceiveOnDestroy();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnExit"))
	void ReceiveOnExit();

private:
	void ExitCondition();
	void RotateAroundSun(const float DeltaTime);
	void SimulateGravity(const float DeltaTime);
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Planet)
	float SunLapsPerSecond = .1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Planet)
	float AxisLapsPerSecond = .25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Planet)
	float Mass = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Planet)
	bool bIsSun;

protected:
	inline static TArray<AT4Planet*> Planets = {};
	inline static TWeakObjectPtr<AT4Planet> Sun = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FHitResult DeathHit;
	
private:
	bool bIsHit;
	float WorldHeight;
	FVector Velocity;
	float GravityConstant = 66743.f;
	bool HasSetStartValues;
	float DistanceFromSun;
	float StartAngle;
	float TimeSinceStart;
};
