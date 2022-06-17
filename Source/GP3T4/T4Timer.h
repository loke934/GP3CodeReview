#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T4Timer.generated.h"

class UTextRenderComponent;
UCLASS()
class GP3T4_API AT4Timer : public AActor
{
	GENERATED_BODY()
	
public:	
	AT4Timer();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void TimerFinished();
	

protected:
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Timer")
	float CountdownTime = 3.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Timer")
	float TextSize = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	bool bTimerIsStarted = false;

};




