#include "T4LightSwitch.h"

void AT4LightSwitch::BeginPlay()
{
	Super::BeginPlay();
	SetLights(bIsOn);
}

void AT4LightSwitch::SetLights(bool bTurnOn)
{
	bIsOn = bTurnOn;
	for (AActor* Light : Lights)
	{
		if (IsValid(Light))
		{
			Light->SetActorHiddenInGame(!bIsOn);
		}
	}
}

void AT4LightSwitch::InteractWithObject()
{
	ReceiveInteractWithObject();
	bIsOn = !bIsOn;
	SetLights(bIsOn);
	RemoveActorsToRemove();
}

void AT4LightSwitch::RemoveActorsToRemove()
{
	if (ActorsToRemove.Num() == 0) {return;}
    	
	for (AActor* ToRemove : ActorsToRemove)
	{
		ToRemove->Destroy();
	}
	ActorsToRemove.Empty();
}

