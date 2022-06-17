// Fill out your copyright notice in the Description page of Project Settings.


#include "T4AIController.h"

#include "T4AIBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"
#include "GP3T4/GP3T4Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"



AT4AIController::AT4AIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AT4AIController::OnPerceptionUpdated);

	PerceptionComponent->bEditableWhenInherited = true;

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight sense"));
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;

	PerceptionComponent->ConfigureSense(*Sight);

	TargetIndex = 0;
	bIsFirstFollowPoint = true;
}

void AT4AIController::BeginPlay()
{
	Super::BeginPlay();

	InitializePawnSettings();
	
	BlackboardComp = GetBlackboardComponent();


	if(DefaultBehaviorToUse == nullptr && ControlledPawn->PawnBehaviorTree == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "No behavior tree selected, Set a behavior tree in the AI Controller or on the pawn");
		UnPossess();
	}
}

void AT4AIController::OnPerceptionUpdated(AActor* Actor, const FAIStimulus Stimulus)
{
	if(ControlledPawn->bHasSeenPlayer)
	{
		return;
	}
	if(AGP3T4Character* Player = Cast<AGP3T4Character>(Actor))
	{
		if(BlackboardComp == nullptr)
		{
			BlackboardComp = GetBlackboardComponent();
		}

		if(Stimulus.WasSuccessfullySensed() && BlackboardComp)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "Sensed player");
			BlackboardComp->SetValueAsBool("bHasSeenPlayer", true);
			BlackboardComp->SetValueAsObject("Player", Player);
			
			ControlledPawn->bHasSeenPlayer = true;
			ControlledPawn->OnNoticedPlayer();
		}
	}
	
}

void AT4AIController::InitializePawnSettings()
{
	ControlledPawn = Cast<AT4AIBaseCharacter>(GetPawn());
	
	if(ControlledPawn->PawnBehaviorTree)
	{
		RunBehaviorTree(ControlledPawn->PawnBehaviorTree);
	}
	else
	{
		RunBehaviorTree(DefaultBehaviorToUse);	
	}
}

//Finds the next target point in array
FVector AT4AIController::GetNextPoint()
{
	if(ControlledPawn == nullptr || ControlledPawn->FollowPoints.IsEmpty() || ControlledPawn->FollowPoints[TargetIndex] == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(1, 10, FColor::Red, "Pawn not set or follow points haven't been set correctly");
		return GetCharacter()->GetActorLocation();
	}

	if(bIsFirstFollowPoint)
	{
		bIsFirstFollowPoint = false;
	}
	else if(ControlledPawn->FollowPoints.Num() > 0)
	{
		if(TargetIndex == ControlledPawn->FollowPoints.Num() - 1 && ControlledPawn->FollowPoints.Num() > 1)
		{
			bIsGoingReverse = true;
			TargetIndex--;
		}
		else if(TargetIndex < ControlledPawn->FollowPoints.Num() - 1 && TargetIndex != 0)
		{
			if(bIsGoingReverse)
			{
				TargetIndex--;
			}
			else
			{
				TargetIndex++;
			}
		}
		else
		{
			if(TargetIndex == 0)
			{
					bIsGoingReverse = false;
					TargetIndex++;
			}
		}
	}

	return ControlledPawn->FollowPoints[TargetIndex]->GetActorLocation();
}
