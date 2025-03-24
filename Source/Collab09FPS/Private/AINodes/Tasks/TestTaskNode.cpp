// Fill out your copyright notice in the Description page of Project Settings.


#include "AINodes/Tasks/TestTaskNode.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UTestTaskNode::UTestTaskNode()
{
	this->NodeName = "Cool Test Node";
}

EBTNodeResult::Type UTestTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};
	AAIController* Controller{OwnerComp.GetAIOwner()};
	const APawn* aiPawn = Controller->GetPawn();

	const FVector Origin{aiPawn->GetActorLocation()};

	const UNavigationSystemV1* NavSystem{UNavigationSystemV1::GetCurrent((GetWorld()))};

	if(IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, 50000.0f, Location))
	{
		Controller->GetBlackboardComponent()->SetValueAsVector(FName(TEXT("V_TargetPosition")), Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UTestTaskNode::GetStaticDescription() const
{
	return TEXT("Heh");
}
