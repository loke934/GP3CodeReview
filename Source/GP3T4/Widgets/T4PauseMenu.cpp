#include "T4PauseMenu.h"

#include "Components/Button.h"
#include "GP3T4/HUD/T4PlayerHUD.h"
#include "Kismet/GameplayStatics.h"

void UT4PauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (MainMenuButton == nullptr || QuitGameButton == nullptr || ResumeGameButton == nullptr){ return;	}

	MainMenuButton->OnClicked.AddDynamic(this, &UT4PauseMenu::MainMenuButtonClicked);
	QuitGameButton->OnClicked.AddDynamic(this, &UT4PauseMenu::QuitGameButtonClicked);
	ResumeGameButton->OnClicked.AddDynamic(this, &UT4PauseMenu::ResumeGameButtonClicked);

	if (GEngine && MainMenuLevel.IsNull())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FString::Printf(TEXT("No main menu level selected in Pause Menu BP")));
	}
}

void UT4PauseMenu::MainMenuButtonClicked()
{
	if (MainMenuLevel.IsNull()){return;}

	UnpauseGame();		
	//Open the Main Menu level/scene/map/whatever unreal wants to call it
	auto LevelName = MainMenuLevel.GetAssetName();
	UGameplayStatics::OpenLevel(GetWorld(), *LevelName);	
}

void UT4PauseMenu::QuitGameButtonClicked()
{
	//Exit the game
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
}

void UT4PauseMenu::ResumeGameButtonClicked()
{
	UnpauseGame();
}

void UT4PauseMenu::UnpauseGame()
{
	auto HUD = GetOwningPlayer() ? Cast<AT4PlayerHUD>(GetOwningPlayer()->GetHUD()) : nullptr;
	if (HUD != nullptr)
	{
		HUD->UnpauseGame(GetOwningPlayer());
	}
}


