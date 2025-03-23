// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collab09FPS/Collab09FPS.h"
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
	ALevelGameState();

public:
	virtual void AddPlayerState(APlayerState* PlayerState) override;

#pragma region World State
	
	UFUNCTION(BlueprintCallable)
	void TransitionWorld();
	void LoadWorld(EWorldState TargetWorldState);
	void UnloadWorlds(EWorldState AvoidWorldState);
	
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "LevelStreaming")
	EWorldState WorldState;

	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "LevelStreaming")
	TMap<EWorldState, TSoftObjectPtr<UWorld>> WorldCollection;

#pragma endregion World State

	UFUNCTION(BlueprintCallable)
	void PlayerSpawned(APawn* pawn);
	UFUNCTION(BlueprintCallable)
	void EnemySpawned(ACharacter* character);
	UFUNCTION(BlueprintCallable)
	void EnemyDespawned(ACharacter* character);

protected:
	UPROPERTY()
	APawn* PlayerPawn;

	UPROPERTY()
	TArray<ACharacter*> EnemyCharacters;
	
private:
	GENERATED_BODY()
};