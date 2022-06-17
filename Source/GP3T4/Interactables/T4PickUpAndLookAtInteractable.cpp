#include "T4PickUpAndLookAtInteractable.h"

#include "Components/SphereComponent.h"
#include "GP3T4/GP3T4Character.h"
#include "GP3T4/PlayerComponents/PickUpAndLookAtComponent.h"
#include "Kismet/GameplayStatics.h"

AT4PickUpAndLookAtInteractable::AT4PickUpAndLookAtInteractable()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

	
}

void AT4PickUpAndLookAtInteractable::InteractWithObject()
{
	Super::InteractWithObject();
	if (bCanBeInteractWith == false) {return;}
	
	auto PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter == nullptr){return;}

	Player = Cast<AGP3T4Character>(PlayerCharacter);
	
	if (Player == nullptr) {return;}

	if (auto PickupComponent = Player->GetPickUpAndLookAtComponent())
	{
		PickupComponent->StartInspectingItem(this);

		//Hide the object and then show it again whenever the delegate is called
		this->SetHidden(true);
		Player->OnRightClick.AddDynamic(this, &AT4PickUpAndLookAtInteractable::UnHideObject);
		bCanBeInteractWith = false;
		OnPickedUp.Broadcast();
	}	
}


void AT4PickUpAndLookAtInteractable::UnHideObject()
{
	Player->OnRightClick.RemoveDynamic(this, &AT4PickUpAndLookAtInteractable::UnHideObject);	
	this->SetHidden(false);
	bCanBeInteractWith = true;
}

