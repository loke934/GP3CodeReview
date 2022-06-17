#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "T4PauseMenu.generated.h"

UCLASS()
class GP3T4_API UT4PauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	void UnpauseGame();
	UFUNCTION() void MainMenuButtonClicked();
	UFUNCTION() void QuitGameButtonClicked();
	UFUNCTION() void ResumeGameButtonClicked();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ResumeGameButton;
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainMenuLevel;
};
