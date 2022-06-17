#pragma once
#include "Engine/GameInstance.h"
#include "T4GameInstance.generated.h"

/**
 * Game Instance handles only audio for now
 */
UCLASS(Abstract)
class GP3T4_API UT4GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "T4|Game Instance",
		meta=(DisplayName = "GetT4GameInstance", WorldContext ="WorldContext"))
	static UT4GameInstance* Get(const UObject* WorldContext);

	UFUNCTION(BlueprintCallable)
	void NextSong(int Level);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetSoundVolume() {return SoundVolume * MasterVolume;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMusicVolume() {return MusicVolume * MasterVolume;}

protected:
	virtual void Init() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnNextSong"))
	void ReceiveOnNextSong();
	
public:
	UPROPERTY(BlueprintReadWrite)
	float MusicVolume = 1.f;

	UPROPERTY(BlueprintReadWrite)
	float SoundVolume = 1.f;

	UPROPERTY(BlueprintReadWrite)
	float MasterVolume = 1.f;

	UPROPERTY(BlueprintReadWrite)
	float SensitivityX = 0.5f;

	UPROPERTY(BlueprintReadWrite)
	float SensitivityY = 0.5f;

	UPROPERTY(BlueprintReadWrite)
	bool InvertAxies;

	UPROPERTY(BlueprintReadOnly)
	int LevelIndex = 0;
	
};
