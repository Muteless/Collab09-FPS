﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "TestTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UTestTaskNode : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTestTaskNode();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
