﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CalculateChasePosition.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UCalculateChasePosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UCalculateChasePosition();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
