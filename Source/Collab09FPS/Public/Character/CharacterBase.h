// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Ability system
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

// Attribute sets
#include "GAS/AttributeSets/HealthAttributeSet.h"
#include "GAS/AttributeSets/AirActionAttributeSet.h"

// Gameplay tags
#include "GameplayTagContainer.h"

// Components
#include "Engine/DataTable.h"

// Structs
#include "Collab09FPS/Collab09FPS.h"
#include "Interfaces/CharacterMovementAbilities.h"

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

UCLASS(Abstract)
class COLLAB09FPS_API ACharacterBase : public ACharacter,
public IAbilitySystemInterface,
public ICharacterMovementAbilities
{
public:
	// Sets default values for this character's properties
	ACharacterBase();

	// Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities.
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	// Override from IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Required movement tags
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "GAS|Tag Requirements|")
	FGameplayTagContainer RequiredMovementTags;

	// Required jump tags
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "GAS|Tag Requirements|")
	FGameplayTag RequiredJumpTag;

	// Jump
	virtual void CharacterMovementJump_Implementation() override;
	
protected:
	// Possessed by controller
	virtual void PossessedBy(AController* NewController) override;

	// Abilities granted when the ability system is initialized
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "GAS")
	TArray<TSubclassOf<UGameplayAbility>> InitialAbilities;

	// Grants initial abilities
	void AddInitialCharacterAbilities();
	
	// Initial gameplay effects
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "GAS")
	TArray<TSubclassOf<UGameplayEffect>> InitialGameplayEffects;

	// Grant initial gameplay effects
	void AddInitialCharacterGameplayEffects();
	
	// Get current health
	UFUNCTION(BlueprintPure,
		Category = "Player|Health|")
	float GetCurrentHealth() const;

	// Get current health
	UFUNCTION(BlueprintPure,
		Category = "Player|Health|")
	float GetMaxHealth() const;

	// Grants initial attribute sets
	virtual void AddInitialCharacterAttributeSets();

	//* Health *//
	// Health attribute set
	UPROPERTY()
	UHealthAttributeSet* HealthAttributeSet;

	//* Data Tables *//
	UPROPERTY(BlueprintReadOnly,
		Category = "GAS")
	TObjectPtr<UDataTable> CharacterAttributeDataTable;

private:
	GENERATED_BODY()
};
