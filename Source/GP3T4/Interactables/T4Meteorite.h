#pragma once

#include "CoreMinimal.h"
#include "T4Interactable.h"
#include "GP3T4/Enums/MeteoriteState.h"
#include "GP3T4/Interfaces/T4CanBeHit.h"
#include "T4Meteorite.generated.h"

class AT4MeteoriteSpawner;
class AGP3T4Character;
class UCameraComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class GP3T4_API AT4Meteorite : public AT4Interactable, public IT4CanBeHit
{
	GENERATED_BODY()
public:	
	AT4Meteorite();

	virtual void InteractWithObject() override;
	virtual void GotHit(AActor* OtherActor) override;

	void Shoot();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void DoFlockingMovement(float DeltaTime);
	
	UFUNCTION()
	FVector CalculateAlignment(TArray<AActor*> OverlappingActors);
	
	UFUNCTION()
	FVector CalculateCohesion(TArray<AActor*> OverlappingActors);
	
	UFUNCTION()
	FVector CalculateSeparation(TArray<AActor*> OverlappingActors);
	
	UFUNCTION()
	FVector CalculateToStayInRadius();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ResetAgent();

	UFUNCTION()
	void Hover();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnDestroy"))
	void ReceiveOnDestroy();

public:
	//Agent State
	UPROPERTY(BlueprintReadOnly)
	EMeteoriteState CurrentState = EMeteoriteState::EMS_Flocking;
	
	//Shooting
	UPROPERTY()
	FVector ShootDirection;

	UPROPERTY(BlueprintReadOnly)
	float LifeSpanShooting;

	UPROPERTY(EditDefaultsOnly, Category ="Meteorite | Shooting State")
	USphereComponent* MeshCollision;
	
	UPROPERTY(EditAnywhere, Category = "Meteorite | Shooting State")
	float TotalLifeSpanShooting = 3.f;

	UPROPERTY(EditAnywhere, Category = " Meteorite | Shooting State")
	float Acceleration = 3000.f;
	
	//Interaction
	UPROPERTY()
	UCameraComponent* CameraComp;

	UPROPERTY()
	AGP3T4Character* PlayerCharacter;

	UPROPERTY(EditAnywhere, Category = "Meteorite | Pick up State")
	float DistanceFromPlayerForward = 100.f;
	
	UPROPERTY(EditAnywhere, Category = "Meteorite | Pick up State")
	float DistanceFromPlayerUp = 25.f;

	UPROPERTY(EditAnywhere, Category = "Meteorite | Pick up State")
	float StartSpeed = 3000.f;
	
	//Agent
	UPROPERTY(EditDefaultsOnly, Category = "Meteorite | Flocking State")
	USphereComponent* Collision;
	
	UPROPERTY(EditDefaultsOnly, Category ="Meteorite | Flocking State")
	float DistanceToNeighbour = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Meteorite | Flocking State")
	float DistanceToObstacles = 200.f;

	UPROPERTY(EditDefaultsOnly, Category ="Meteorite | Flocking State")
	float Speed = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category ="Meteorite | Flocking State")
	float MaxSpeed = 150.f;

	//Lerping
	UPROPERTY(EditDefaultsOnly, Category ="Meteorite | Flocking State")
	float RotationLerp = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category ="Meteorite | Flocking State")
	float MoveLerp = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, Category ="Meteorite | Flocking State")
	float CohesionLerp = 0.5f;

	//Stay within radius
	UPROPERTY()
	AT4MeteoriteSpawner* OriginPosition;

	UPROPERTY(EditDefaultsOnly, Category = "Meteorite | Flocking State")
	float MaxDistToOrigin = 800.f;
	
	UPROPERTY(EditAnywhere, Category = "Meteorite | Pick up State | Hover Effect")
	float RadiusX = 1.f;
	UPROPERTY(EditAnywhere, Category = "Meteorite | Pick up State | Hover Effect")
	float RadiusY = 1.f;
	UPROPERTY(EditAnywhere, Category = "Meteorite | Pick up State | Hover Effect")
	float RadiusZ = 1.f;

	UPROPERTY(EditAnywhere, Category = "Meteorite | Pick up State | Hover Effect")
	float RateX = 3.f;
	UPROPERTY(EditAnywhere, Category = "Meteorite | Pick up State | Hover Effect")
	float RateY = 5.f;
	UPROPERTY(EditAnywhere, Category = "Meteorite | Pick up State | Hover Effect")
	float RateZ = 4.f;

	UPROPERTY(EditAnywhere, Category = "Meteorite | Pick up State | Hover Effect")
	float OffsetX = 15.f;
	UPROPERTY(EditAnywhere, Category = "Meteorite | Pick up State | Hover Effect")
	float OffsetY = 25.f;
	UPROPERTY(EditAnywhere, Category = "Meteorite | Pick up State | Hover Effect")
	float OffsetZ = 25.f;
	
private:
	float ShootSpeed;
};
