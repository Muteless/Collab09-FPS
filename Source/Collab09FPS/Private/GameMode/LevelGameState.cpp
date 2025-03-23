// Fill out your copyright notice in the Description page of Project Settings.


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

void ALevelGameState::TransitionWorld()
{
	switch (WorldState)
	{
		case EWorldState::WorldOne:
			LoadWorld(EWorldState::WorldTwo);
		case EWorldState::WorldTwo:
			LoadWorld(EWorldState::WorldOne);
	}
}

void ALevelGameState::LoadWorld(EWorldState TargetWorldState)
{
	for (const TPair<EWorldState, TSoftObjectPtr<UWorld>>& World : WorldCollection)
	{
		if (World.Key == TargetWorldState)
		{
			// Set world state to new target world state
			WorldState = TargetWorldState;
			
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = FName("WorldLoaded");
			
			// Stream level
			UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(),
				World.Value,
				true,
				false,
				LatentInfo);
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