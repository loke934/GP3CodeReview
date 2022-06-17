#include "T4Timer.h"
#include "Components/TextRenderComponent.h"

AT4Timer::AT4Timer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AT4Timer::BeginPlay()
{
	Super::BeginPlay();
}

void AT4Timer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTimerIsStarted)
	{
		CountdownTime -= DeltaTime;
		if (CountdownTime <= 0.f)
		{
			TimerFinished();
			bTimerIsStarted = false;
		}
	}
}

void AT4Timer::StartTimer()
{
	bTimerIsStarted = true;
}




