// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/LevelData/LevelDataAsset.h"
#include "UObject/Interface.h"
#include "GameInstanceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLAB09FPS_API IGameInstanceInterface
{
public:
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	ULevelDataAsset* GetLevelData();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	int GetWorldIndex();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void SetWorldIndex(int NewIndex);
	
private:
	GENERATED_BODY()

};
