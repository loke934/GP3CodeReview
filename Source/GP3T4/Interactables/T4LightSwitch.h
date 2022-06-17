#pragma once
#include "T4Interactable.h"
#include "T4LightSwitch.generated.h"

UCLASS()
class GP3T4_API AT4LightSwitch : public AT4Interactable
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void SetLights(bool bTurnOn);

protected:
	virtual void InteractWithObject() override;

private:
	void RemoveActorsToRemove();

public:
	UPROPERTY(EditAnywhere)
	bool bIsOn;

	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> Lights;

	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> ActorsToRemove;
};
