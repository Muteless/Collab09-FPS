// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/LevelData/LevelDataAsset.h"
#include "PersistentData/SaveGameData.h"
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
#pragma region WorldState
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	ULevelDataAsset* GetLevelData();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	int GetWorldIndex();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void SetWorldIndex(int NewIndex);

#pragma endregion WorldState

#pragma region Save&Load
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	FString GetSaveSlot();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void SetSaveSlot(FName SlotName);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void LoadGame();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	USaveGameData* GetSaveGameData();

#pragma endregion Save&Load
	
private:
	GENERATED_BODY()
};
