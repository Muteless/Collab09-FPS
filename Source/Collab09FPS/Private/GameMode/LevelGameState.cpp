// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LevelGameState.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

ALevelGameState::ALevelGameState():
WorldState(),
PlayerPawn(nullptr)
{
	
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
			FLatentActionInfo LatentInfo;
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

void ALevelGameState::UnloadWorlds(EWorldState AvoidWorldState)
{
	for (const TPair<EWorldState, TSoftObjectPtr<UWorld>>& World : WorldCollection)
	{
		if (World.Key != AvoidWorldState)
		{
			FLatentActionInfo LatentInfo;
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