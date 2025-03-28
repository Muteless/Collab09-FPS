// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistentData/SaveGameData.h"

EWorldState USaveGameData::GetWorldState_Implementation()
{
	return WorldState;
}

void USaveGameData::SetWorldState_Implementation(EWorldState NewWorldState)
{
	WorldState = NewWorldState;
}

ULevelDataAsset* USaveGameData::GetLevelDataAsset_Implementation()
{
	return LevelDataAsset;
}

void USaveGameData::SetLevelDataAsset_Implementation(ULevelDataAsset* NewLevelDataAsset)
{
	LevelDataAsset = NewLevelDataAsset;
}

int USaveGameData::GetCheckpointIndex_Implementation()
{
	return CheckpointIndex;
}

void USaveGameData::SetCheckpointIndex_Implementation(int NewCheckpointIndex)
{
	CheckpointIndex = NewCheckpointIndex;
}

UPlayerSaveData* USaveGameData::GetPlayerSaveData_Implementation()
{
	return PlayerSaveData;
}

void USaveGameData::SetPlayerSaveData_Implementation(UPlayerSaveData* NewPlayerSaveData)
{
	PlayerSaveData = NewPlayerSaveData;
}
