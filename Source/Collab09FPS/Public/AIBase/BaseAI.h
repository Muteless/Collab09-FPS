// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "BaseAI.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class COLLAB09FPS_API ABaseAI : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAI();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Category="Base AI",
		meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category="Base AI",
		meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category="Base AI",
		meta = (AllowPrivateAccess = true)
		)
	TObjectPtr<UBlackboardComponent> BlackboardComponent;
	
};
