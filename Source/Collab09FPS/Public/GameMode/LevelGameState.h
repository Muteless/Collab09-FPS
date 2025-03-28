// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collab09FPS/Collab09FPS.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"

#include "Interfaces/GameInstanceInterface.h"
#include "Interfaces/GameStateInterface.h"
#include "Interfaces/LoadInterface.h"
#include "Interfaces/SaveGameInterface.h"

#include "WorldObjects/Checkpoint.h"

#include "LevelGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorldTransition, EWorldState, NewWorldState);

/**
 * 
 */

UCLASS()
class COLLAB09FPS_API ALevelGameState :
public AGameStateBase,
public ILoadInterface,
public IGameStateInterface,
public IGameInstanceInterface
{
	ALevelGameState();

public:
	virtual void BeginPlay() override;
	virtual void AddPlayerState(APlayerState* PlayerState) override;

	virtual void LoadData_Implementation(USaveGame* SaveGame) override;

#pragma region World State

	UPROPERTY(BlueprintAssignable)
	FOnWorldTransition OnWorldTransition;

	UFUNCTION()
	void WorldLoaded();
	
	UFUNCTION(BlueprintCallable)
	void TransitionWorld_Implementation() override;
	void LoadWorld(EWorldState TargetWorldState);
	void UnloadWorlds(EWorldState AvoidWorldState);
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "LevelStreaming")
	EWorldState WorldState;

	UPROPERTY()
	TMap<EWorldState, TSoftObjectPtr<UWorld>> WorldCollection;

#pragma endregion World State

#pragma region CheckpointSystem

	UFUNCTION(BlueprintCallable)
	void SetCheckpointIndex_Implementation(int NewCheckPointIndex) override;
	
	UFUNCTION(BlueprintCallable)
	void GetAllCheckpoints();

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> Checkpoints;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	int CheckpointIndex = 0;

#pragma endregion CheckpointSystem

#pragma region Save&Load

	
	
#pragma endregion Save&Load

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