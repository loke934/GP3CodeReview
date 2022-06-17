#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "T4PlayerHUD.generated.h"

UCLASS()
class GP3T4_API AT4PlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ConstructPauseMenu(APlayerController* PlayerController);
	void UnpauseGame(APlayerController* PlayerController);

protected:
	/*
	 * Pause menu stuff
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PauseMenuClass;

	//Todo Create a new PauseMenu class that we change this to
	UPROPERTY(EditAnywhere)
	class UT4PauseMenu* PauseMenu;

	UPROPERTY()
	bool bIsPaused = false;
};
