#include "T4GameInstance.h"

UT4GameInstance* UT4GameInstance::Get(const UObject* WorldContext)
{
	const UWorld* World = WorldContext->GetWorld();
	return World->GetGameInstance<UT4GameInstance>();
}

void UT4GameInstance::NextSong(int Level)
{
	LevelIndex = Level;
	ReceiveOnNextSong();
}

void UT4GameInstance::Init()
{
	Super::Init();
	//todo set volume from file here
}

