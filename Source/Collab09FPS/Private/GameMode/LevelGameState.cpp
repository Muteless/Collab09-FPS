﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LevelGameState.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

ALevelGameState::ALevelGameState():
WorldState(),
PlayerPawn(nullptr)
{
	
}

void ALevelGameState::BeginPlay()
{
	// Get level data asset world collection
	ULevelDataAsset* LevelDataAsset = IGameInstanceInterface::Execute_GetLevelData(GetGameInstance());
	if (LevelDataAsset)
	{
		WorldCollection = LevelDataAsset->WorldCollection;
	}

	// Load initial world
	LoadWorld(WorldState);
	
	Super::BeginPlay();
}

#pragma region World State

void ALevelGameState::TransitionWorld_Implementation()
{
	switch (WorldState)
	{
		case EWorldState::WorldOne:
			LoadWorld(EWorldState::WorldTwo);
			break;
		case EWorldState::WorldTwo:
			LoadWorld(EWorldState::WorldOne);
			break;
	}
}

void ALevelGameState::LoadWorld(EWorldState TargetWorldState)
{
	for (const TPair<EWorldState, TSoftObjectPtr<UWorld>>& World : WorldCollection)
	{
		if (World.Key == TargetWorldState)
		{
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = FName("WorldLoaded");
			LatentInfo.Linkage = 0;
			LatentInfo.UUID = __LINE__;
			
			// Stream level
			UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(),
				World.Value,
				true,
				false,
				LatentInfo);

			// Set world state to new target world state
			WorldState = TargetWorldState;
		}
	}

	// Unload irrelevant worlds
	UnloadWorlds(TargetWorldState);
}

void ALevelGameState::WorldLoaded()
{
	OnWorldTransition.Broadcast(WorldState);
}

void ALevelGameState::UnloadWorlds(EWorldState AvoidWorldState)
{
	for (const TPair<EWorldState, TSoftObjectPtr<UWorld>>& World : WorldCollection)
	{
		if (World.Key != AvoidWorldState)
		{
			FLatentActionInfo LatentInfo;

			// Unload level
			UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(),
				World.Value,
				LatentInfo,
				false);
		}
	}
}

#pragma endregion World State


void ALevelGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
	
	if (PlayerState->GetPlayerController()->GetPawn())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "A Player has spawned");	
	}
}

void ALevelGameState::LoadData_Implementation(USaveGame* SaveGame)
{
	WorldState = ISaveGameInterface::Execute_GetWorldState(SaveGame);
	LoadWorld(WorldState);

	CheckpointIndex = ISaveGameInterface::Execute_GetCheckpointIndex(SaveGame);
}

#pragma region CheckpointSystem

void ALevelGameState::SetCheckpointIndex_Implementation(int NewCheckPointIndex)
{
	CheckpointIndex = NewCheckPointIndex;
}

void ALevelGameState::GetAllCheckpoints()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckpoint::StaticClass(), Checkpoints);
}

#pragma endregion CheckpointSystem

void ALevelGameState::PlayerSpawned(APawn* pawn)
{
	PlayerPawn = pawn;
}

void ALevelGameState::EnemySpawned(ACharacter* character)
{
	if (!EnemyCharacters.Contains(character))
		EnemyCharacters.Add(character);
}

void ALevelGameState::EnemyDespawned(ACharacter* character)
{
	if (EnemyCharacters.Contains(character))
		EnemyCharacters.Remove(character);
}