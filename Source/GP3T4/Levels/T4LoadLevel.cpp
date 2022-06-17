#include "T4LoadLevel.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GP3T4/Interfaces/IsPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


AT4LoadLevel::AT4LoadLevel()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerComponent");
	RootComponent = TriggerBox;

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AT4LoadLevel::LoadLevel);
}

void AT4LoadLevel::BeginPlay()
{
	Super::BeginPlay();

	if (LevelToChangeTo.IsNull())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				30,
				FColor::Red,
				FString::Printf(TEXT("NO LEVEL SELECTED OH NOOO")));
		}
	}
}

void AT4LoadLevel::LoadLevel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("collided")));
	}
	
	//Make sure that it is the player that is overlapping & that a level has been set on the BP
	bool bIsCorrectLevelAndActor = LevelToChangeTo.IsNull() || (OtherActor && !OtherActor->Implements<UIsPlayerCharacter>());
	if (bIsCorrectLevelAndActor){    return;    }

	//Open the new level
	auto LevelName = LevelToChangeTo.GetAssetName();
	UGameplayStatics::OpenLevel(GetWorld(), *LevelName);
}