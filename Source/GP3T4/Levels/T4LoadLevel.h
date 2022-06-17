#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T4LoadLevel.generated.h"

UCLASS()
class GP3T4_API AT4LoadLevel : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION() void LoadLevel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	AT4LoadLevel();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> LevelToChangeTo;

public:

};