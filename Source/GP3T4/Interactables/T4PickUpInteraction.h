#pragma once

#include "CoreMinimal.h"
#include "T4Interactable.h"
#include "T4PickUpInteraction.generated.h"

class UCameraComponent;
class AGP3T4Character;
UCLASS()
class GP3T4_API AT4PickUpInteraction : public AT4Interactable
{
	GENERATED_BODY()
	
	virtual void InteractWithObject() override;
	
	void DropObject();

public:
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	float DistanceFromPlayerForward = 100.f;
	
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	float DistanceFromPlayerUp = 25.f;

private:
	bool bIsCarrying;

	UPROPERTY()
	AGP3T4Character* PlayerCharacter;

	UPROPERTY()
	UCameraComponent* CameraComp;
};
