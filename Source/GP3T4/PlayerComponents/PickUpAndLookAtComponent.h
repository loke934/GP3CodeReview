#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GP3T4/Enums/PlayerCondition.h"
#include "GP3T4/Interactables/T4PickUpAndLookAtInteractable.h"
#include "PickUpAndLookAtComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP3T4_API UPickUpAndLookAtComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPickUpAndLookAtComponent();
	friend class AGP3T4Character;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY()
	AGP3T4Character* Character;

	UPROPERTY()
	EPlayerCondition CurrentPlayerState;

	UPROPERTY(VisibleAnywhere)
	AT4PickUpAndLookAtInteractable* PickedUpItem;

	UPROPERTY()
	APlayerCameraManager* CameraManger;

	bool bIsInspecting = false;

public:
	void StartInspectingItem(AT4PickUpAndLookAtInteractable* Item);
	void StopInspectingItem();
	
};
