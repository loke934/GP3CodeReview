#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "T4MenuWidget.generated.h"

UCLASS()
class GP3T4_API UT4MenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetupMenu(UWorld* LevelToLoadOnStartButtonClicked);

protected:
	virtual void NativeConstruct() override;
	UFUNCTION() void StartButtonClicked();
	UFUNCTION() void QuitButtonClicked();

private:
	UPROPERTY(meta  = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta  = (BindWidget))
	UButton* QuitButton;

	UPROPERTY()
	UWorld* LevelToChangeTo;
};
