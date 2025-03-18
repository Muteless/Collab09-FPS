// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "LevelGameState.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API ALevelGameState : public AGameStateBase
{
	GENERATED_BODY()
	ALevelGameState()
	{
		
	}

	virtual void AddPlayerState(APlayerState* PlayerState) override;

protected:
	APawn* PlayerPawn;
	TArray<ACharacter*> EnemyCharacters;
	

public:
	UFUNCTION(BlueprintCallable)
	void PlayerSpawned(APawn* pawn);
	UFUNCTION(BlueprintCallable)
	void EnemySpawned(ACharacter* character);
	UFUNCTION(BlueprintCallable)
	void EnemyDespawned(ACharacter* character);
	
};
