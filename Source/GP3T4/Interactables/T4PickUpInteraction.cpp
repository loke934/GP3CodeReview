#include "T4PickUpInteraction.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GP3T4/GP3T4Character.h"
#include "Kismet/GameplayStatics.h"

void AT4PickUpInteraction::InteractWithObject()
{
	//No base implementation
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5,
			FColor::Emerald,
			FString::Printf(TEXT("This can be picked up!!")));
	}

	if (bIsCarrying)
	{
		DropObject();
		bIsCarrying = false;
	}
	else
	{
		//Todo, this could be moved to character and modified as well as the interaction behavior.
		PlayerCharacter = Cast<AGP3T4Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		if (PlayerCharacter == nullptr) { return;}
		CameraComp = PlayerCharacter->GetFirstPersonCameraComponent();
	
		SetActorLocation( CameraComp->GetComponentLocation() + (CameraComp->GetForwardVector() * DistanceFromPlayerForward) -CameraComp->GetUpVector() * DistanceFromPlayerUp);
		SetActorRotation(FRotator::ZeroRotator);
		const FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepWorld, true);
		AttachToComponent(CameraComp,AttachmentRules, NAME_None);
		
		bIsCarrying = true;
	}
	
}

void AT4PickUpInteraction::DropObject()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

}
