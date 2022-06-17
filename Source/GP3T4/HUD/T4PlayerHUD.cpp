#include "T4PlayerHUD.h"

#include "Blueprint/UserWidget.h"
#include "GP3T4/Widgets/T4PauseMenu.h"
#include "Kismet/GameplayStatics.h"


void AT4PlayerHUD::ConstructPauseMenu(APlayerController* PlayerController)
{
	if (PlayerController == nullptr) {return;}

	//todo Pause should be handled by the gamemode/gameinstance
	//Pause / Unpause
	bIsPaused = !bIsPaused;	
	UGameplayStatics::SetGamePaused(GetWorld(), bIsPaused);

	if (PauseMenuClass)
	{
		if (PauseMenu == nullptr)
		{
			PauseMenu = CreateWidget<UT4PauseMenu>(PlayerController, PauseMenuClass);
			PauseMenu->AddToViewport();
		}
		
		//PauseMenu = PauseMenu == nullptr ? CreateWidget<UT4PauseMenu>(PlayerController, PauseMenuClass) : PauseMenu;
		if (PauseMenu && bIsPaused)
		{
			// Show/Hide cursor & focus on the widget
			PauseMenu->SetVisibility(ESlateVisibility::Visible);
			
			FInputModeGameAndUI InputModeData;
			InputModeData.SetWidgetToFocus(PauseMenu->TakeWidget());
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(bIsPaused);
		}
		else
		{
			if (PauseMenu) {/*PauseMenu->RemoveFromParent();*/ PauseMenu->SetVisibility(ESlateVisibility::Hidden);}			
				
			FInputModeGameOnly InputModeData;	
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(bIsPaused);	
		}
	}
}

void AT4PlayerHUD::UnpauseGame(APlayerController* PlayerController)
{
	if (PlayerController == nullptr) {return;}
	if (PauseMenu) {/*PauseMenu->RemoveFromParent();*/ PauseMenu->SetVisibility(ESlateVisibility::Hidden);}

	bIsPaused = false;
	UGameplayStatics::SetGamePaused(GetWorld(), bIsPaused);
				
	FInputModeGameOnly InputModeData;	
	PlayerController->SetInputMode(InputModeData);
	PlayerController->SetShowMouseCursor(bIsPaused);	
}


