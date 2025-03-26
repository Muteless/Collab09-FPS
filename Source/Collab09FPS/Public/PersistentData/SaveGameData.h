// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "GameMode/LevelData/LevelDataAsset.h"
#include "Player/PlayerSaveData.h"

#include "SaveGameData.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API USaveGameData : public USaveGame
{
public:
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	ULevelDataAsset* LevelDataAsset = nullptr;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	int CheckpointIndex = 0;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	UPlayerSaveData* PlayerSaveData;
	
private:
	GENERATED_BODY()
};
