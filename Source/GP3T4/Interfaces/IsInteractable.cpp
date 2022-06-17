#include "IsInteractable.h"

void IIsInteractable::InteractWithObject()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("InteractWithObject is not overriden for this actor.")));
	}
}
