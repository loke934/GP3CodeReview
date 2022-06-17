#pragma once

UENUM(BlueprintType)
enum class EPlayerCondition : uint8
{
   EPC_Moving UMETA(DisplayName = "Normal State"),
   EPC_Inspecting UMETA(DisplayName = "Inspecting object"),
   EPC_MAX UMETA(DisplayName = "MAX")
};

