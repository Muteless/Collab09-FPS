// Fill out your copyright notice in the Description page of Project Settings.


#include "AINodes/Tasks/CalculateChasePosition.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PawnMovementComponent.h"

UCalculateChasePosition::UCalculateChasePosition()
{
}

EBTNodeResult::Type UCalculateChasePosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	if (!Controller) return EBTNodeResult::Failed;

	APawn* AIPawn = Controller->GetPawn();
	if (!AIPawn) return EBTNodeResult::Failed;

	// Get Blackboard
	UBlackboardComponent* BlackboardComp = Controller->GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;

	// Get target actor (player)
	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("O_PlayerObject")));
	if (!TargetActor) return EBTNodeResult::Failed;

	// Get positions
	const FVector TargetLocation = TargetActor->GetActorLocation();
	const FVector LastKnownLocation = BlackboardComp->GetValueAsVector(TEXT("V_LastKnownPlayerPosition"));
	const float PlayerMoveThreshold = 100.0f; // Distance before AI recalculates position

	// Only update if player moved significantly
	if (FVector::DistSquared(TargetLocation, LastKnownLocation) < FMath::Square(PlayerMoveThreshold))
	{
		return EBTNodeResult::Succeeded; // No need to update
	}

	// Save the new player position
	BlackboardComp->SetValueAsVector(TEXT("V_LastKnownPlayerPosition"), TargetLocation);

	// Find closest point on a circle around the player
	const float ChaseRadius = 300.0f; // Distance AI keeps from player
	const FVector AILocation = AIPawn->GetActorLocation();
	FVector DirectionToPlayer = (TargetLocation - AILocation).GetSafeNormal();
	FVector DesiredPosition = TargetLocation - (DirectionToPlayer * ChaseRadius);

	// Use navigation system to find closest valid point
	FNavLocation NavLocation;
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem && NavSystem->ProjectPointToNavigation(DesiredPosition, NavLocation))
	{
		BlackboardComp->SetValueAsVector(TEXT("V_TargetPosition"), NavLocation.Location);


		Controller->MoveToLocation(NavLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed; // Couldn't find a valid navigation point
}



FString UCalculateChasePosition::GetStaticDescription() const
{
	return TEXT("Node that decides the chase position the enemy will move to");
}
