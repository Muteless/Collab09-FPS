// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBase/BaseAI.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
ABaseAI::ABaseAI()
{
	//Creation of Blackboard and Behaviour Tree
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void ABaseAI::BeginPlay()
{
	Super::BeginPlay();

	//Starts running the behaviour tree
	if (IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}
}

void ABaseAI::OnPossess(APawn* InPawn)
{
	//Initial set up of blackboard, the blackboard WILL not work unless this is run first
	if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());		
	}

	Super::OnPossess(InPawn);
}

