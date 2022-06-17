// Fill out your copyright notice in the Description page of Project Settings.


#include "T4TriggerBase.h"

#include "GP3T4/GP3T4Character.h"
#include "GP3T4/Interfaces/T4IsOverlapping.h"

// Sets default values
AT4TriggerBase::AT4TriggerBase()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AT4TriggerBase::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AT4TriggerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AT4TriggerBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AGP3T4Character* Player = Cast<AGP3T4Character>(OtherActor))
	{
			TriggerEffect();
	}
}

//Executes the trigger effect on all actors
void AT4TriggerBase::TriggerEffect()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "Overlapped");

	if(Actors.Num() > 0)
	{
		for(int i = 0; i < Actors.Num(); i++)
		{
			if(Actors[i].TargetActor != nullptr)
			{
				IT4IsOverlapping* OverlappingInterface = Cast<IT4IsOverlapping>(Actors[i].TargetActor);
				if(Actors[i].TargetActor->GetClass()->ImplementsInterface(IT4IsOverlapping::UClassType::StaticClass()))
				{
					if(Actors[i].bIsSingleUse && Actors[i].bHasBeenUsed){}
					else
					{
						Actors[i].bHasBeenUsed = true;
						GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "Triggered Effect");
						OverlappingInterface->Execute_OnOverlapTriggered(Actors[i].TargetActor);	
					}
				}
			}
		}
	}
}

void AT4TriggerBase::OnOverlapTriggered_Implementation()
{
	IT4IsOverlapping::OnOverlapTriggered_Implementation();
}


