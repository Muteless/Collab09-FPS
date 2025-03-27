// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawner/AISpawner.h"
#include "NavigationSystem.h"
#include "AIBase/BaseAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


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

	// Get all spawners in the scene
	TArray<AActor*> AllSpawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAISpawner::StaticClass(), AllSpawners);

	// Assign a unique ID based on position in array
	SpawnerID = AllSpawners.IndexOfByKey(this);
	UE_LOG(LogTemp, Log, TEXT("Spawner ID assigned: %d"), SpawnerID);

	// Ensure ArrowComponent is valid
	ArrowComponent = FindComponentByClass<UArrowComponent>();
	if (!ArrowComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("ArrowComponent is missing from AISpawner %d!"), SpawnerID);
	}

	// Apply initial active state safely
	if (bStartActive)
	{
		EnableSpawner();
	}
	else
	{
		DisableSpawner();
	}

	// Only spawn if active and valid
	if (IsActive)
	{
		if (SpawnMode == ESpawnMode::OnStart)
			SpawnEnemy();

		if (RespawnMode == ERespawnMode::OnTimer)
		{
			StartSpawnTimer();
		}
	}
}




void AAISpawner::SpawnEnemy()
{

	if (RespawnMode == ERespawnMode::Never && SpawnedCount > 0) return;
	if (SpawnedCount >= MaxEnemyCount)
	{
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
		EnemySpawnType = EnemyBlueprints[2];
		break;
	default:
		break;
	}

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
	if (!NavSystem) return;

	FVector SpawnLocation = GetActorLocation();
	FNavLocation ClosestNavPoint;

	bool FoundLocation = NavSystem->ProjectPointToNavigation(SpawnLocation, ClosestNavPoint);

	if (FoundLocation)
	{
		FVector AdjustedSpawnLocation = ClosestNavPoint.Location + FVector(0, 0, 50); // Raise by 50 units

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor* SpawnedEnemy = World->SpawnActor<AActor>(
			EnemySpawnType, AdjustedSpawnLocation,
			FRotationMatrix::MakeFromX(ArrowComponent->GetForwardVector()).Rotator(),
			SpawnParams);

		if (IsValid(SpawnedEnemy))
		{
			SpawnedCount++;

			ABaseAI* AIC = Cast<ABaseAI>(Cast<APawn>(SpawnedEnemy)->GetController());

			if (IsValid(AIC))
			{

				FTimerHandle DelayHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUObject(this, &AAISpawner::DelayedSetBlackboardValue, AIC, EnemyStartBehaviour);
				GetWorldTimerManager().SetTimer(DelayHandle, TimerDelegate, .1f, false);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("AIC Not Valid"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn enemy at: %s"), *ClosestNavPoint.Location.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn enemy at no valid NavLocation"));
	}
}


void AAISpawner::DelayedSetBlackboardValue(ABaseAI* AIC, EDefaultSpawnBehaviour Behaviour)
{
	if (!AIC || !AIC->GetBlackboardComponent()) return;

	UBlackboardComponent* BlackboardComp = AIC->GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	if (!BlackboardComp->IsValidKey(BlackboardComp->GetKeyID(FName(TEXT("E_AIStartStateEnumKey")))))
	{
		return;
	}

	switch (Behaviour)
	{
	case EDefaultSpawnBehaviour::Idle:
		UE_LOG(LogTemp, Log, TEXT("Idle"));
		BlackboardComp->SetValueAsInt(FName(TEXT("E_AIStartStateEnumKey")), 1);
		break;
	case EDefaultSpawnBehaviour::Patrol:
		UE_LOG(LogTemp, Log, TEXT("Patrol"));
		BlackboardComp->SetValueAsInt(FName(TEXT("E_AIStartStateEnumKey")), 0);
		break;
	case EDefaultSpawnBehaviour::RandomWander:
		UE_LOG(LogTemp, Log, TEXT("Random Wander"));
		BlackboardComp->SetValueAsInt(FName(TEXT("E_AIStartStateEnumKey")), 2);
		break;
	case EDefaultSpawnBehaviour::AutoTargetPlayer:
		UE_LOG(LogTemp, Log, TEXT("Auto Target Player"));
		BlackboardComp->SetValueAsInt(FName(TEXT("E_AIStartStateEnumKey")), 3);
		break;
	}

	UE_LOG(LogTemp, Log, TEXT("Set Blackboard Value to: %d"),
		BlackboardComp->GetValueAsInt(FName(TEXT("E_AIStartStateEnumKey"))));
}

void AAISpawner::EnableSpawner()
{
	this->IsActive = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	UE_LOG(LogTemp, Log, TEXT("Spawner %d enabled"), SpawnerID);
}

void AAISpawner::DisableSpawner()
{
	this->IsActive = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	UE_LOG(LogTemp, Log, TEXT("Spawner %d disabled"), SpawnerID);
}

void AAISpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Clear the spawn timer if it's still active
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	}
}






