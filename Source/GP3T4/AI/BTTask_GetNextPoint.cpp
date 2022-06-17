// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetNextPoint.h"

#include "T4AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_GetNextPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AT4AIController* Controller = Cast<AT4AIController>(OwnerComp.GetAIOwner());
	if(Controller)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("GetNextPoint",Controller->GetNextPoint());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
