#pragma once

#include "CoreMinimal.h"
#include "T4Interactable.h"
#include "T4PushInteraction.generated.h"

/**
 * 
 */
UCLASS()
class GP3T4_API AT4PushInteraction : public AT4Interactable
{
	GENERATED_BODY()

	virtual void InteractWithObject() override;
	
};
