// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SaveGame.h"
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
#pragma region WorldState
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "WorldState")
	ULevelDataAsset* GetLevelData();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "WorldState")
	int GetWorldIndex();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "WorldState")
	void SetWorldIndex(int NewIndex);

#pragma endregion WorldState

#pragma region Level

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Level")
	void TransitionLevel(const int WorldIndex);

#pragma endregion Level

#pragma region Save&Load
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Save&Load")
	FString GetSaveSlot();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Save&Load")
	void SetSaveSlot(FName SlotName);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Save&Load")
	USaveGame* LoadGame();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Save&Load")
	void SaveGame();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Save&Load")
	USaveGame* GetSaveGameData();

#pragma endregion Save&Load
	
private:
	GENERATED_BODY()
};
