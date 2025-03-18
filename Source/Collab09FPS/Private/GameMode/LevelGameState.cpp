// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LevelGameState.h"
#include "GameFramework/PlayerState.h"


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
