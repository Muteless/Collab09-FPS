// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "GameMode/LevelData/LevelDataAsset.h"
#include "PersistentData/PlayerSaveDataStruct.h"

#include "Interfaces/SaveGameInterface.h"

#include "Player/PlayerSaveData.h"

#include "SaveGameData.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API USaveGameData :
public USaveGame,
public ISaveGameInterface
{
public:
	
	#pragma region World

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "World")
	EWorldState WorldState;
	UFUNCTION()
	virtual EWorldState GetWorldState_Implementation() override;
	UFUNCTION()
	virtual void SetWorldState_Implementation(EWorldState NewWorldState) override;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "World")
	TArray<int> InactiveSpawnersIds;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "World")
	ULevelDataAsset* LevelDataAsset = nullptr;
	UFUNCTION()
	virtual ULevelDataAsset* GetLevelDataAsset_Implementation() override;
	UFUNCTION()
	virtual void SetLevelDataAsset_Implementation(ULevelDataAsset* NewLevelDataAsset) override;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "World")
	int CheckpointIndex = 0;
	UFUNCTION()
	virtual int GetCheckpointIndex_Implementation() override;
	UFUNCTION()
	virtual void SetCheckpointIndex_Implementation(int NewCheckpointIndex) override;
	
	#pragma endregion World

	UFUNCTION()
	virtual FPlayerData GetPlayerSaveData_Implementation() override;
	UFUNCTION()
	virtual void SetPlayerSaveData_Implementation(const FPlayerData& NewPlayerData) override;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Player")
	FPlayerData PlayerSaveData = FPlayerData();
	
private:
	GENERATED_BODY()
};
