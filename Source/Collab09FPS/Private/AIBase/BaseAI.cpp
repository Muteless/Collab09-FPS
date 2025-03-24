// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBase/BaseAI.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"


// Sets default values
ABaseAI::ABaseAI()
{
	//Creation of Blackboard and Behaviour Tree
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	
	
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
}

void ABaseAI::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(PerceptionComponent))
	{
		this->PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAI::OnTargetPerceived);
	}
	
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

	Blackboard->SetValueAsObject(FName(TEXT("O_SelfActor")), InPawn);

	Super::OnPossess(InPawn);
}

void ABaseAI::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor) return;

	FAISenseID senseType = Stimulus.Type;
	bool wasSensed = Stimulus.WasSuccessfullySensed();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	bool isPlayer = (Cast<ACharacter>(Actor) == PlayerCharacter);
	
	if (senseType == UAISense::GetSenseID<UAISense_Sight>())
	{
		if (wasSensed)
		{
			if (isPlayer)
			{
				BlackboardComponent->SetValueAsObject(TEXT("O_PlayerObject"), Actor);
			}
		}
		else
		{
		}
	}
	else if (senseType == UAISense::GetSenseID<UAISense_Hearing>())
	{
		if (wasSensed)
		{
			
		}
		else
		{
		}
	}
}


