// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"
#include "GameFramework/SaveGame.h"
#include "PersistentData/SaveGameData.h"

#include "Interfaces/GameInstanceInterface.h"
#include "Interfaces/SaveGameInterface.h"

#include "NativeGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameSaved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameLoaded);

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UNativeGameInstance :
public UGameInstance,
public IGameInstanceInterface
{
public:
	virtual void Init() override;
	
	virtual void Shutdown() override;
	
#pragma region Delegates

	UPROPERTY(BlueprintAssignable,
		Category = "Events")
	FGameSaved OnGameSaved;

	UPROPERTY(BlueprintAssignable,
		Category = "Events")
	FGameLoaded OnGameLoaded;
	
#pragma endregion Delegates
	
#pragma region WorldState

	virtual int GetWorldIndex_Implementation() override;
	virtual ULevelDataAsset* GetLevelData_Implementation() override;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "World State")
	int WorldIndex = 0;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "World State")
	TArray<ULevelDataAsset*> WorldData;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "World State")
	TSoftObjectPtr<UWorld> WorldToTransitionTo = nullptr;

#pragma endregion WorldState
	
#pragma region SaveGame
	
	virtual void SaveGame_Implementation() override;
	virtual USaveGame* GetSaveGameData_Implementation() override;
	virtual void SetSaveSlot_Implementation(FName SlotName) override;
	virtual FString GetSaveSlot_Implementation() override;
	
	virtual USaveGame* LoadGame_Implementation() override;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Save Game")
	FString SaveSlot = "Default";

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Save Game")
	int32 SaveSlotIndex = 0;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Save Game")
	USaveGame* SaveGame = nullptr;

#pragma endregion SaveGame
	
private:
	GENERATED_BODY()
};
