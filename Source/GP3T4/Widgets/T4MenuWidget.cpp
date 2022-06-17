#include "T4MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UT4MenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton == nullptr || QuitButton == nullptr)
	{
		return;
	}
	
	StartButton->OnClicked.AddDynamic(this, &UT4MenuWidget::StartButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UT4MenuWidget::QuitButtonClicked);
}

void UT4MenuWidget::SetupMenu(UWorld* LevelToLoad)
{
	if (LevelToLoad == nullptr)
	{
		return;
	}

	LevelToChangeTo = LevelToLoad;
}

void UT4MenuWidget::StartButtonClicked()
{
	if (LevelToChangeTo == nullptr)
	{
		return;
	}

	auto LevelName = LevelToChangeTo->GetName();	
	UGameplayStatics::OpenLevel(GetWorld(), *LevelName);
}

void UT4MenuWidget::QuitButtonClicked()
{
	//todo See if there is a better way to quit the game 
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
}