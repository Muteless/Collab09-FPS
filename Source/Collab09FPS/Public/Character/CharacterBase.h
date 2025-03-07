// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Ability system
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

// Attribute sets
#include "GAS/AttributeSets/HealthAttributeSet.h"
#include "GAS/AttributeSets/AirActionAttributeSet.h"

// Gameplay tags
#include "GameplayTagContainer.h"

// Components
#include "Engine/DataTable.h"

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

UCLASS(Abstract)
class COLLAB09FPS_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
public:
	// Sets default values for this character's properties
	ACharacterBase();
	
	// Override from IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities.
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
protected:
	// Possessed by controller
	virtual void PossessedBy(AController* NewController) override;

	// Abilities granted when the ability system is initialized
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "GAS|Abilities|")
	TArray<TSubclassOf<UGameplayAbility>> InitialAbilities;

	// Grants initial attribute sets
	void AddInitialCharacterAttributeSets();
	
	// Grants initial abilities
	void AddInitialCharacterAbilities();
	
	// Required movement tags
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "GAS|Tag Requirements|")
	FGameplayTagContainer RequiredMovementTags;
	
	//* Health *//
	// Health attribute set
	UPROPERTY()
	UHealthAttributeSet* HealthAttributeSet;

	// Get current health
	UFUNCTION(BlueprintPure,
		Category = "Player|Health|")
	float GetCurrentHealth() const;

	// Get current health
	UFUNCTION(BlueprintPure,
		Category = "Player|Health|")
	float GetMaxHealth() const;

	//* Air Actions *//
	// AirAction attribute set
	UPROPERTY()
	UAirActionAttributeSet* AirActionAttributeSet;

	// Get current air actions
	UFUNCTION(BlueprintPure,
		Category = "Player|Actions|")
	float GetCurrentAirActions() const;

	// Get current air actions
	UFUNCTION(BlueprintPure,
		Category = "Player|Actions|")
	float GetMaxAirActions() const;

	//* Data Tables *//
	// Health attribute data table
	UPROPERTY(BlueprintReadOnly,
		Category = "GAS|Data Tables|")
	TObjectPtr<UDataTable> HealthAttributeDataTable;

	// Air actions attribute data table
	UPROPERTY(BlueprintReadOnly,
		Category = "GAS|Data Tables|")
	TObjectPtr<UDataTable> AirActionAttributeDataTable;

private:
	GENERATED_BODY()
};
