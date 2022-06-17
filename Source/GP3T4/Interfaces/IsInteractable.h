#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IsInteractable.generated.h"

UINTERFACE()
class UIsInteractable : public UInterface
{
	GENERATED_BODY()
};

class GP3T4_API IIsInteractable
{
	GENERATED_BODY()

public:
	virtual void InteractWithObject();
};
