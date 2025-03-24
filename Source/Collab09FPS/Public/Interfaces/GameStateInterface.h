// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameStateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGameStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLAB09FPS_API IGameStateInterface
{
public:
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void TransitionWorld();
	
private:
	GENERATED_BODY()
};
