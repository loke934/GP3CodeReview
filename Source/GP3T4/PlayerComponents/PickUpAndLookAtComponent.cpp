#include "PickUpAndLookAtComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GP3T4/GP3T4Character.h"
#include "Kismet/GameplayStatics.h"

UPickUpAndLookAtComponent::UPickUpAndLookAtComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPickUpAndLookAtComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPickUpAndLookAtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPickUpAndLookAtComponent::StartInspectingItem(AT4PickUpAndLookAtInteractable* Item)
{
	if (Character == nullptr || Item == nullptr) {return;}

	Character->DisablePlayerMovement(true);	
	PickedUpItem = Item;

	if (PickedUpItem->GetItemMesh())
	{

		bIsInspecting = true;
		
		UStaticMesh* Mesh = PickedUpItem->GetItemMesh()->GetStaticMesh();		
		Character->SetMeshToInspect(Mesh, PickedUpItem->MeshScaleWhenPickedUp, PickedUpItem->ZOffsetWhenPickedUp);

		if (const auto World = GetWorld())
		{
			CameraManger = CameraManger == nullptr ? UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0) : CameraManger;
			if (CameraManger == nullptr || Character == nullptr) { return; }

			//Lock camera
			CameraManger->ViewYawMax = Character->GetPlayerViewpointRotation().Yaw;
			CameraManger->ViewYawMin = Character->GetPlayerViewpointRotation().Yaw;

			CameraManger->ViewPitchMax = Character->GetPlayerViewpointRotation().Pitch;
			CameraManger->ViewPitchMin = Character->GetPlayerViewpointRotation().Pitch;
		}
	}	
}

void UPickUpAndLookAtComponent::StopInspectingItem()
{
	if (Character == nullptr){return;}

	bIsInspecting = false;

	Character->LockPlayerLookRotation(false);	
	Character->SetMeshToInspect(nullptr, 0, 0);
	
}

