#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T4MovingApple.generated.h"

UCLASS()
class GP3T4_API AT4MovingApple : public AActor
{
	GENERATED_BODY()
	
public:
	AT4MovingApple();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void StartMovingTowardsPlayer(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category= "Apple")
	UStaticMeshComponent* AppleMesh;

	UPROPERTY(VisibleAnywhere, Category= "Apple")
	class USphereComponent* AppleAggroRadius;

	UPROPERTY(EditAnywhere, Category= "Apple")
	float StopMovingRange = 250.f;

	UPROPERTY(EditAnywhere, Category= "Apple")
	float FollowSpeed = 500.f;

	UPROPERTY()
	AActor* PlayerActor;

	UPROPERTY()
	bool bShouldFollowPlayer = false;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnStartMoving"))
	void ReceiveStartMoving();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnSTopMoving"))
	void ReceiveStopMoving();
};
