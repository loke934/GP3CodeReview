#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T4MeteoriteSpawner.generated.h"

class AT4Meteorite;
UCLASS()
class GP3T4_API AT4MeteoriteSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AT4MeteoriteSpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SpawnAgents();

	UPROPERTY(EditDefaultsOnly, Category = "Flocking")
	TSubclassOf<AT4Meteorite> ClassToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Flocking")
	int NumberOfAgents = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Flocking")
	float SpawnRangeMin = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Flocking")
	float SpawnRangeMax = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Flocking")
	TArray<AT4Meteorite*> Agents;
};

