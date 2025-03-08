// Fill out your copyright notice in the Description page of Project Settings.

#include "Collab09FPS/Public/Character/CharacterBase.h"

// Constructor
ACharacterBase::ACharacterBase()
{
	//* Ability System Component *//
	// Create AbilitySystemComponent
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	// Create attribute sets
	HealthAttributeSet = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("Health Attribute Set"));
}

// AbilitySystemComponent interface, return ability system component
UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Make the character jump
void ACharacterBase::CharacterMovementJump_Implementation()
{
	Jump();
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
		AddInitialCharacterAbilities();

		// Add initial effects to ability system
		AddInitialCharacterGameplayEffects();
	}
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterBase::AddInitialCharacterAttributeSets()
{
	if (AbilitySystemComponent)
	{
		// Initialize attribute sets
		// Health
		AbilitySystemComponent->InitStats(UHealthAttributeSet::StaticClass(),
			CharacterAttributeDataTable);

		// Air Actions
		AbilitySystemComponent->InitStats(UAirActionAttributeSet::StaticClass(),
			CharacterAttributeDataTable);
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
			// Create an outgoing spec for the Gameplay Effect
			FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect,1.f, AbilitySystemComponent->MakeEffectContext());
			// Apply the effect to the Ability System Component
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}
	}
}

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