// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GAS/AbilitySystemComponentBase.h"
#include "GameplayAbilities/Public/AbilitySystemInterface.h"
#include "GAS/AttributeSets/HealthAttributeSet.h"
#include "GAS/AttributeSets/StaminaAttributeSet.h"

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
	
protected:
	// Possessed by controller
	virtual void PossessedBy(AController* NewController) override;

	// Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "GAS | ")
	UAbilitySystemComponent* AbilitySystemComponent;

	// Abilities granted when the ability system is initialized
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS | Abilities | ")
	TArray<TSubclassOf<UGameplayAbility>> InitialAbilities;

	// Grants initial abilities
	void AddInitialCharacterAbilities();

	//* Health *//
	// Health attribute set
	UPROPERTY()
	UHealthAttributeSet* HealthAttributeSet;

	// Get current health
	UFUNCTION(BlueprintPure, Category = "Player | Health | ")
	float GetCurrentHealth() const;

	//* Stamina *//
	// Stamina attribute set
	UPROPERTY()
	UStaminaAttributeSet* StaminaAttributeSet;

	// Get current stamina
	UFUNCTION(BlueprintPure, Category = "Player | Stamina | ")
	float GetCurrentStamina() const;

private:
	GENERATED_BODY()

};
