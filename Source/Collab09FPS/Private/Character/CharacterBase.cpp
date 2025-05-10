// Fill out your copyright notice in the Description page of Project Settings.

#include "Collab09FPS/Public/Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/AttributeSets/StaminaAttributeSet.h"
#include "Interfaces/CharacterController.h"

#pragma region Initialization

// Constructor
ACharacterBase::ACharacterBase()
{
	//* Ability System Component *//
	// Create AbilitySystemComponent
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

// AbilitySystemComponent interface, return ability system component
UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Get the character movement component
UCharacterMovementComponent* ACharacterBase::GetActorCharacterMovementComponent_Implementation()
{
	return GetCharacterMovement();
}

// Called when character has been possessed
void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Initialize AbilitySystemComponent
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		
		// Set initial character attribute sets
		AddInitialCharacterAttributeSets();
		
		// Add initial character abilities to ability system
		AddNativeCharacterAbilities();
		AddInitialCharacterAbilities();

		// Add initial effects to ability system
		AddInitialCharacterGameplayEffects();
	}

	LevelGameState = Cast<ALevelGameState>(GetWorld()->GetGameState());
	if (LevelGameState)
	{
		LevelGameState->OnWorldTransition.AddDynamic(this, &ACharacterBase::HandleWorldTransition);
	}
}

void ACharacterBase::HandleWorldTransition(EWorldState WorldState)
{
	
}

void ACharacterBase::AddInitialCharacterAttributeSets()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AddSet<UHealthAttributeSet>();
		BindHealthAttributeSet();

		AbilitySystemComponent->AddSet<UAirActionAttributeSet>();
		AbilitySystemComponent->AddSet<UMetaEffectsAttributeSet>();
	}
}

// Give native character abilities
void ACharacterBase::AddNativeCharacterAbilities()
{
	if (NativeAbilities.Num() > 0)
	{
		for (TSubclassOf<UNativeGameplayAbility> Ability : NativeAbilities)
		{
			if (Ability)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
			}
		}
	}
}

// Add initial character abilities
void ACharacterBase::AddInitialCharacterAbilities()
{
	if (AbilitySystemComponent)
	{
		for (TSubclassOf<UGameplayAbility> Ability : InitialAbilities)
		{
			// if ability is valid
			if (Ability != nullptr)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
			}
		}
	}
}


void ACharacterBase::AddInitialCharacterGameplayEffects()
{
	if (AbilitySystemComponent)
	{
		for (TSubclassOf<UGameplayEffect> GameplayEffect : InitialGameplayEffects)
		{
			// Valid gameplay effect
			if (GameplayEffect)
			{
				// Create an outgoing spec for the Gameplay Effect
				FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect,1.f, AbilitySystemComponent->MakeEffectContext());
			
				// Apply the effect to the Ability System Component
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			}
		}
	}
}

void ACharacterBase::BindHealthAttributeSet()
{
	// Health
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	(HealthAttributeSet->GetCurrentHealthAttribute()).AddUObject
	(this, &ACharacterBase::OnHealthChanged);

	// Shields
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	(HealthAttributeSet->GetCurrentFireShieldAttribute()).AddUObject
	(this, &ACharacterBase::OnFireShieldChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	(HealthAttributeSet->GetCurrentCurseShieldAttribute()).AddUObject
	(this, &ACharacterBase::OnCurseShieldChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	(HealthAttributeSet->GetCurrentBloodShieldAttribute()).AddUObject
	(this, &ACharacterBase::OnBloodShieldChanged);
}

void ACharacterBase::BindAirActionAttributeSet()
{
	
}

void ACharacterBase::BindCMCAttributeSet()
{
	
}

void ACharacterBase::BindDashAttributeSet()
{
	
}

void ACharacterBase::BindMetaEffectsAttributeSet()
{
	
}

#pragma endregion Initialization

#pragma region AttributeChangeDelegates

void ACharacterBase::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	// if health is less or equal than zero, die
	if (Data.NewValue <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health is less or equal than zero, death."));
		Death();
	}
}

void ACharacterBase::OnFireShieldChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0)
	{
		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->RemoveGameplayCue(FGameplayTag::RequestGameplayTag(FName("GameplayCue.Effect.ElementalShield.Fire")));
		}
	}
}

void ACharacterBase::OnCurseShieldChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0)
	{
		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->RemoveGameplayCue(FGameplayTag::RequestGameplayTag(FName("GameplayCue.Effect.ElementalShield.Curse")));
		}
	}
}

void ACharacterBase::OnBloodShieldChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0)
	{
		if (AbilitySystemComponent)
		{
			FGameplayTagContainer EffectTags;
			EffectTags.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayCue.Effect.ElementalShield.Blood")));
			AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTags);
		}
	}
}

void ACharacterBase::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	
}

void ACharacterBase::OnAirActionsChanged(const FOnAttributeChangeData& Data)
{
	
}

#pragma endregion AttributeChangeDelegates

#pragma region Input

FVector ACharacterBase::GetMovementInput_Implementation()
{
	return GetLastMovementInputVector();
}

#pragma endregion Input

#pragma region Actions

// On landed
void ACharacterBase::Landed(const FHitResult& Hit)
{
	Execute_CharacterMovementLanded(this);
	Super::Landed(Hit);
}

void ACharacterBase::Death_Implementation()
{
	Destroy();
}

#pragma endregion Actions

#pragma region GAS

//* Blueprint Helper functions *//
// Get current health attribute
float ACharacterBase::GetCurrentHealth() const
{
	if (HealthAttributeSet)
	{
		return HealthAttributeSet->GetCurrentHealth();
	}
	return -1.0f;
}

// Get max health
float ACharacterBase::GetMaxHealth() const
{
	if (HealthAttributeSet)
	{
		return HealthAttributeSet->GetMaxHealth();
	}
	return -1.0f;
}

// Get current air actions
float ACharacterBase::GetCurrentAirActions() const
{
	if (AirActionAttributeSet)
	{
		return AirActionAttributeSet->GetCurrentAirActions();
	}
	return -1.0f;
}

// Get max air actions
float ACharacterBase::GetMaxAirActions() const
{
	if (AirActionAttributeSet)
	{
		return AirActionAttributeSet->GetMaxAirActions();
	}
	return -1.0f;
}

#pragma endregion GAS
