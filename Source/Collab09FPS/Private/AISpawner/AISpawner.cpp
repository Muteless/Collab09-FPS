// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawner/AISpawner.h"

#include "NavigationSystem.h"


void AAISpawner::StartSpawnTimer()
{
	if (SpawnTime > 0)
	{
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAISpawner::SpawnEnemy, SpawnTime, true);
	}
}


// Sets default values
AAISpawner::AAISpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ArrowComponent = GetComponentByClass<UArrowComponent>();
}

void AAISpawner::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("begin!"));


	if (ArrowComponent == nullptr)
		ArrowComponent = GetComponentByClass<UArrowComponent>();

	if (SpawnMode == ESpawnMode::OnStart)
		SpawnEnemy();

	if (RespawnMode == ERespawnMode::OnTimer)
	{
		StartSpawnTimer();
	}
}

void AAISpawner::SpawnEnemy()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawned!"));

	
	if (RespawnMode == ERespawnMode::Never && SpawnedCount > 0) return;
	if (SpawnedCount >= MaxEnemyCount)
	{
		// Only stop the timer if respawning is set to OnTimer
		if (RespawnMode == ERespawnMode::OnTimer)
		{
			GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		}
		return;
	}

	UWorld* World = GetWorld();
	if (!World) return;

	TSubclassOf<AActor> EnemySpawnType;

	switch (EnemyType)
	{
	case EEnemyTypes::Melee:
		break;
	case EEnemyTypes::Ranger:
		EnemySpawnType = EnemyBlueprints[1];
		break;
	case EEnemyTypes::DeepSeek:
		EnemySpawnType = EnemyBlueprints[0];
		break;
	case EEnemyTypes::HeavyMelee:
		break;
	case EEnemyTypes::HeavyRanger:
		break;
	default:
		break;
	}

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

	if (!NavSystem) return;

	FVector SpawnLocation = GetActorLocation();
	FNavLocation ClosestNavPoint;

	bool FoundLocation = NavSystem->ProjectPointToNavigation(
		SpawnLocation,
		ClosestNavPoint
	);

	if (FoundLocation)
	{
		AActor* SpawnedEnemy = World->SpawnActor<AActor>(EnemySpawnType,
			ClosestNavPoint.Location, FRotationMatrix::MakeFromX(ArrowComponent->GetForwardVector()).Rotator());

		if (IsValid(SpawnedEnemy))
		{
			SpawnedCount++;
			UE_LOG(LogTemp, Log, TEXT("Spawned Enemy at: %s"), *ClosestNavPoint.Location.ToString());
		}
		else
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn enemy at: %s"), *ClosestNavPoint.Location.ToString());
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn enemy at no valid NavLocation"));
}


