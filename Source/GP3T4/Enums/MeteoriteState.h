#pragma once

UENUM(BlueprintType)
enum class EMeteoriteState : uint8
{
   EMS_Flocking = 0 UMETA(DisplayName = "Flocking State"),
   EMS_PickedUp = 1 UMETA(DisplayName = "Picked Up State"),
   EMS_Shooting = 2 UMETA(DisplayName = "Shooting State"),
   EMS_MAX = 3 UMETA(DisplayName = "MAX")
 };


