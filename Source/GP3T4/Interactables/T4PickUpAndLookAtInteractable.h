#pragma once

#include "CoreMinimal.h"
#include "T4Interactable.h"
#include "GP3T4/GP3T4Character.h"
#include "T4PickUpAndLookAtInteractable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickedUp);

UCLASS()
class GP3T4_API AT4PickUpAndLookAtInteractable : public AT4Interactable
{
	GENERATED_BODY()
	
	
protected:
	AT4PickUpAndLookAtInteractable();	
	virtual void InteractWithObject() override;

	UFUNCTION(BlueprintCallable)
	void UnHideObject();

public:
	UPROPERTY(EditAnywhere)
	float MeshScaleWhenPickedUp = 0.25f;

	UPROPERTY(EditAnywhere)
	float ZOffsetWhenPickedUp = 0.f;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPickedUp OnPickedUp;

protected:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ItemMesh;

	UPROPERTY()
	AGP3T4Character* Player;

	bool bCanBeInteractWith = true;


public:
	FORCEINLINE UStaticMeshComponent* GetItemMesh(){return ItemMesh;}
	
};
