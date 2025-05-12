// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/CharacterMovementComponentBase.h"

// Ability system
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GAS/Abilities/Native/NativeGameplayAbility.h"
#include "GameplayEffectTypes.h"

// Attribute sets
#include "GAS/AttributeSets/HealthAttributeSet.h"
#include "GAS/AttributeSets/AirActionAttributeSet.h"
#include "GAS/AttributeSets/DashAttributeSet.h"
#include "GAS/AttributeSets/CMCAttributeSet.h"
#include "GAS/AttributeSets/MetaEffectsAttributeSet.h"

// Components
#include "Engine/DataTable.h"
#include "GameMode/LevelGameState.h"

// Interfaces
#include "Interfaces/MovementComponentAttributeUpdate.h"
#include "Interfaces/CharacterMovementAbilities.h"
#include "Interfaces/CharacterInput.h"

// Structs
#include "Collab09FPS/Collab09FPS.h"

#include "CharacterBase.generated.h"

/**
 * @class ACharacterBase
 * @brief Abstract base class for characters that integrates with the Gameplay Ability System.
 *
 * ACharacterBase serves as a foundation for implementing characters in the game that utilize the
 * Gameplay Ability System (GAS) for managing abilities, attributes, and other player-related features.
 * This class extends ACharacter and implements the IAbilitySystemInterface to integrate with GAS.
 *
 * Key functionalities include:
 * - Managing the Ability System Component, which is required for GAS.
 * - Providing access attribute sets.
 * - Binding player input functions and managing possession by controllers.
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterDeath, AActor*, Actor);

UCLASS(Abstract)
class COLLAB09FPS_API ACharacterBase : public ACharacter,
public ICharacterInput,
public IAbilitySystemInterface,
public ICharacterMovementAbilities,
public IMovementComponentAttributeUpdate
{
public:
	// Sets default values for this character's properties
	ACharacterBase();

	UPROPERTY(BlueprintAssignable)
	FOnCharacterDeath OnCharacterDeath;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	ALevelGameState* LevelGameState;

	UFUNCTION()
	virtual void HandleWorldTransition(EWorldState WorldState);

#pragma region Input
	
	UFUNCTION(Category = "Input")
	virtual FVector GetMovementInput_Implementation() override;

#pragma endregion Input

#pragma region Components
	
	// Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities.
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	// Override from IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Get Character Movement Component
	virtual UCharacterMovementComponent* GetActorCharacterMovementComponent_Implementation() override;

#pragma endregion Components

#pragma region AttributeChangeDelegates

	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	
	virtual void OnFireShieldChanged(const FOnAttributeChangeData& Data);
	virtual void OnCurseShieldChanged(const FOnAttributeChangeData& Data);
	virtual void OnBloodShieldChanged(const FOnAttributeChangeData& Data);
	
	virtual void OnStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void OnAirActionsChanged(const FOnAttributeChangeData& Data);
	
#pragma endregion AttributeChangeDelegates
	
#pragma region Actions
	
	// Death
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void Death();
	void Death_Implementation();

#pragma endregion Actions
	
protected:
	// Possessed by controller
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void Landed(const FHitResult& Hit) override;
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "GAS")
	TArray<TSubclassOf<UGameplayEffect>> OnLandedEffects;

	#pragma region Initialization
		
		// Grants native abilities
		void AddNativeCharacterAbilities();
		// Abilities granted when the ability system is initialized
		UPROPERTY(EditDefaultsOnly, meta = (AdvancedDisplay = "NativeAbilities"))
		TArray<TSubclassOf<UNativeGameplayAbility>> NativeAbilities;
		
		// Grants initial abilities
		void AddInitialCharacterAbilities();
		// Abilities granted when the ability system is initialized
		UPROPERTY(EditDefaultsOnly,
			BlueprintReadOnly,
			Category = "GAS")
		TArray<TSubclassOf<UGameplayAbility>> InitialAbilities;
		
		// Grant initial gameplay effects
		void AddInitialCharacterGameplayEffects();
		// Initial gameplay effects
		UPROPERTY(EditDefaultsOnly,
			BlueprintReadOnly,
			Category = "GAS")
		TArray<TSubclassOf<UGameplayEffect>> InitialGameplayEffects;

		virtual void BindHealthAttributeSet();
		virtual void BindAirActionAttributeSet();
		virtual void BindCMCAttributeSet();
		virtual void BindDashAttributeSet();
		virtual void BindMetaEffectsAttributeSet();
		
	#pragma endregion Initialization
	
	//* Health *//
	// Health attribute set
	UPROPERTY()
	UHealthAttributeSet* HealthAttributeSet;
	
	// Get current health
	UFUNCTION(BlueprintPure,
		Category = "Default|Health|")
	float GetCurrentHealth() const;

	// Get current health
	UFUNCTION(BlueprintPure,
		Category = "Default|Health|")
	float GetMaxHealth() const;

	//* Air Actions *//
	// AirAction attribute set
	UPROPERTY()
	UAirActionAttributeSet* AirActionAttributeSet;
	
	// Get current air actions
	UFUNCTION(BlueprintPure,
		Category = "Default|Actions|")
	float GetCurrentAirActions() const;

	// Get current air actions
	UFUNCTION(BlueprintPure,
		Category = "Default|Actions|")
	float GetMaxAirActions() const;

	//* Meta Effects *//
	// Meta effects attribute aet
	UPROPERTY()
	UMetaEffectsAttributeSet* MetaEffectsAttributeSet;
	
	// Grants initial attribute sets
	virtual void AddInitialCharacterAttributeSets();

private:
	GENERATED_BODY()
};
