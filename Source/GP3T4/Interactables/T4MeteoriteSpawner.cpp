#include "T4MeteoriteSpawner.h"
#include "T4Meteorite.h"
#include "Kismet/KismetMathLibrary.h"

AT4MeteoriteSpawner::AT4MeteoriteSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AT4MeteoriteSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnAgents();
}

void AT4MeteoriteSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AT4MeteoriteSpawner::SpawnAgents()
{
	for (int i = 0; i < NumberOfAgents; ++i)
	{
		FVector Result = FMath::VRand();
		Result *= FMath::RandRange(SpawnRangeMin,SpawnRangeMax);
		FVector SpawnPosition = GetActorLocation() + Result;
		AT4Meteorite* SpawnedAgent = GetWorld()->SpawnActor<AT4Meteorite>(ClassToSpawn, SpawnPosition, UKismetMathLibrary::RandomRotator());
		SpawnedAgent->OriginPosition = this;

		//Todo maybe move out behaviour to be controlled from this class.
		Agents.Add(SpawnedAgent);
	}
}
