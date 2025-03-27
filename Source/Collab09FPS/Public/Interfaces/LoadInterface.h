// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UObject/Interface.h"
#include "LoadInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class ULoadInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLAB09FPS_API ILoadInterface
{
public:
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void LoadData(USaveGame* SaveGame);

private:
	GENERATED_BODY()
};
