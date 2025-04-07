// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawner/AISpawner.h"

#include "AbilitySystemComponent.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AAISpawner::AAISpawner()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComponent->SetCapsuleSize(25, 88);
	RootComponent = CapsuleComponent;
	
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(CapsuleComponent);
}

void AAISpawner::StartSpawnTimer()
{
	if (SpawnTime > 0)
	{
		GetWorldTimerManager().SetTimer(SpawnTimerHandle,
		this,
			&AAISpawner::SpawnEnemy,
			SpawnTime,
			true);
	}
}

void AAISpawner::BeginPlay()
{
	Super::BeginPlay();
	
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
}

void AAISpawner::SpawnEnemy()
{
	if (!IsActive) return;

	
		// If spawner is never meant to spawn and spawned count is greater than zero
		if (RespawnMode == ERespawnMode::Never && SpawnedCount > 0) return;

		// if we have spawned everything there is to spawn
		if (SpawnedCount >= MaxEnemyCount)
		{
			if (RespawnMode == ERespawnMode::OnTimer)
			{
				// Clear the timer if respawn mode is set to timer mode
				GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
			}
			return;
		}

		UWorld* World = GetWorld();
		if (!World) return;

		TSubclassOf<AActor> EnemySpawnType;

		// Set the right type of enemy to spawn based on EnemyBlueprints array
		switch (Enemy)
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

		// Find navigation system
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

				for (TMap<TSubclassOf<UGameplayEffect>, float>::TIterator Effect(InitialGameplayEffects); Effect; ++Effect)
				{
					// If the provided effect is invalid -> return early
					if (!Effect.Key())
					{
						UE_LOG(LogTemp, Error, TEXT("Invalid effect class."))
						return;
					}

					UAbilitySystemComponent* AbilitySystemComponent = SpawnedEnemy->FindComponentByClass<UAbilitySystemComponent>();
					
					if (AbilitySystemComponent)
					{
						// Apply initial gameplay effects
						// Make effect context
						FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
						EffectContext.AddSourceObject(this);
	
						// Create an Outgoing Effect Spec
						FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect.Key(),
							1.f,
							EffectContext);
						EffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(
							FGameplayTag::RequestGameplayTag(FName("Data.Magnitude")),
							Effect.Value());
						
						AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
					}
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

	// Only spawn if active and valid
	if (IsActive)
	{
		if (SpawnMode == ESpawnMode::OnStart)
		{
			SpawnEnemy();
		}
		
		if (RespawnMode == ERespawnMode::OnTimer)
		{
			StartSpawnTimer();
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("Spawner %d enabled"), SpawnerID);
}

void AAISpawner::DisableSpawner()
{
	this->IsActive = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	UE_LOG(LogTemp, Log, TEXT("Spawner %d disabled"), SpawnerID);
}

void AAISpawner::ToggleSpawner()
{
	if (!IsActive)
		EnableSpawner();
	else
		DisableSpawner();
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






