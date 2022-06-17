#include "T4PushInteraction.h"

void AT4PushInteraction::InteractWithObject()
{
	//Currently we dont want the base implementation running
	//Super::InteractWithObject();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("This can be pushed!")));
	}

	SetActorLocation(GetActorLocation() + FVector(0,0,100.f));	
}
