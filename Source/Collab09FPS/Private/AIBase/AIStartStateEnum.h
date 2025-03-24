// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "Collab09FPS/Collab09FPS.h"
#include "AIStartStateEnum.generated.h"


/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UAIStartStateEnum : public UBlackboardKeyType_Enum
{
	GENERATED_BODY()
public:
	UAIStartStateEnum()
	{
		EnumType = StaticEnum<EDefaultSpawnBehaviour>();
	}
};
