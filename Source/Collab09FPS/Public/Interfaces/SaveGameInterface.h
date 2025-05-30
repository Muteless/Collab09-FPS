﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "GameMode/LevelData/LevelDataAsset.h"
#include "PersistentData/PlayerSaveDataStruct.h"

#include "SaveGameInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USaveGameInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLAB09FPS_API ISaveGameInterface
{
public:
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	ULevelDataAsset* GetLevelDataAsset();
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void SetLevelDataAsset(ULevelDataAsset* NewLevelDataAsset);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	int GetCheckpointIndex();
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void SetCheckpointIndex(int NewCheckpointIndex);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	FPlayerData GetPlayerSaveData();
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void SetPlayerSaveData(const FPlayerData& NewPlayerData);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	EWorldState GetWorldState();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void SetWorldState(EWorldState NewWorldState);
	
private:
	GENERATED_BODY()
};
