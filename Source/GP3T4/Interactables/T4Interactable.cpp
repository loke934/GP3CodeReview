#include "T4Interactable.h"

#include "Components/SphereComponent.h"
#include "GP3T4/Interfaces/IsPlayerCharacter.h"

AT4Interactable::AT4Interactable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AT4Interactable::BeginPlay()
{
	Super::BeginPlay();
}

void AT4Interactable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AT4Interactable::InteractWithObject()
{
	//super should not be called for this method in child classes
	if (bIsInteractable) {ReceiveInteractWithObject();}
}

/*
 * Outline Stuff
 */
void AT4Interactable::EnableOutline(bool bShowOutline)
{
	//always disable outline if object is not interactable
	if (!bIsInteractable) {bShowOutline = false;}
	
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	for (auto Component : Components)
	{
		Component->SetCustomDepthStencilValue(252);
		Component->MarkRenderStateDirty();
		Component->SetRenderCustomDepth(bShowOutline);
	}
}

