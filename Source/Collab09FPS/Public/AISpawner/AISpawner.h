// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Collab09FPS/Collab09FPS.h"
#include "AIBase/BaseAI.h"
#include "GameplayEffect.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"

#include "AISpawner.generated.h"

UCLASS()
class COLLAB09FPS_API AAISpawner : public AActor
{
	GENERATED_BODY()

public:
	AAISpawner();
	
	UPROPERTY()
	bool IsActive;

	UPROPERTY()
	bool bStartActive = true;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Enemy Spawner",
		meta = (AllowPrivateAccess = "true"))
	int SpawnerID;

	UPROPERTY(BlueprintReadWrite,
		EditAnywhere,
		Category = "Default")
	EEnemyTypes Enemy;

	UPROPERTY(BlueprintReadWrite,
		EditAnywhere,
		Category = "Default")
	TMap<TSubclassOf<UGameplayEffect>, float> InitialGameplayEffects;

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "Default",
		meta = (AllowPrivateAccess = "true"))
	EDefaultSpawnBehaviour EnemyStartBehaviour;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		Category = "Default",
		meta = (AllowPrivateAccess = "true"))
	ESpawnMode SpawnMode;

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "Default",
		meta = (EditCondition = "FEnemySpawnEntry.RespawnMode==ERespawnMode::OnTimer",
			EditConditionHides, ClampMin=1)) 
	float SpawnTime = 1;

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "Default",
		meta = (EditCondition = "SpawnMode==ESpawnMode::OnEvent || RespawnMode==ERespawnMode::OnTimer",
			EditConditionHides, ClampMin=1, SliderExponent=1, Delta=1, Multiple=1)) 
	int MaxEnemyCount = 5;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
	Category = "Default",
	meta = (AllowPrivateAccess = "true"))
	ERespawnMode RespawnMode = ERespawnMode::Never;

	UPROPERTY()
	FTimerHandle SpawnTimerHandle;
	
	//TArray of all the enemy blueprints relating to the Enum
	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "Enemy Spawner",
		meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AActor>> EnemyBlueprints;
	
	int SpawnedCount;

	UPROPERTY()
	UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY()
	UArrowComponent* ArrowComponent;

	void StartSpawnTimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpawnEnemy();
	void DelayedSetBlackboardValue(ABaseAI* AIC, EDefaultSpawnBehaviour Behaviour);
	
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void EnableSpawner();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void DisableSpawner();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void ToggleSpawner();
	
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

public:
};
