// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBase/BaseAI.h"
#include "Collab09FPS/Collab09FPS.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "AISpawner.generated.h"

UCLASS()
class COLLAB09FPS_API AAISpawner : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		Category = "Enemy Spawner",
		meta = (AllowPrivateAccess = "true"))
	EEnemyTypes EnemyType = EEnemyTypes::DeepSeek;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		Category = "Enemy Spawner",
		meta = (AllowPrivateAccess = "true"))
	ESpawnMode SpawnMode = ESpawnMode::OnStart;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
	Category = "Enemy Spawner",
	meta = (AllowPrivateAccess = "true"))
	ERespawnMode RespawnMode = ERespawnMode::Never;

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "Enemy Spawner",
		meta = (EditCondition = "SpawnMode==ESpawnMode::OnEvent || RespawnMode==ERespawnMode::OnTimer",
			EditConditionHides, ClampMin=1, SliderExponent=1, Delta=1, Multiple=1)) 
	int MaxEnemyCount = 5;

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "Enemy Spawner",
		meta = (EditCondition = "RespawnMode==ERespawnMode::OnTimer",
			EditConditionHides, ClampMin=1)) 
	float SpawnTime = 1;
	
	//TArray of all the enemy blueprints relating to the Enum
	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "Enemy Spawner",
		meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AActor>> EnemyBlueprints;

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category = "Enemy Spawner",
		meta = (AllowPrivateAccess = "true"))
	EDefaultSpawnBehaviour EnemyStartBehaviour;
	
	int SpawnedCount;

	UArrowComponent* ArrowComponent;


	FTimerHandle SpawnTimerHandle;

	void StartSpawnTimer();
	
	// Sets default values for this actor's properties
	AAISpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpawnEnemy();
	void DelayedSetBlackboardValue(ABaseAI* AIC, EDefaultSpawnBehaviour Behaviour);

public:
};
