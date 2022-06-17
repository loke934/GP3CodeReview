#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ELevelNames : uint8
{
	ELN_Bedroom UMETA(DisplayName = "Bedroom" ),
	ELN_Level1 UMETA(DisplayName = "Level1"),
	ELN_Level2 UMETA(DisplayName = "Level2"),
	ELN_MAX UMETA(DisplayName = "MaxLevels")
	
};
