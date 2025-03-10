// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/CharacterMovementComponentBase.h"

// Ability system
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

// Attribute sets
#include "GAS/AttributeSets/HealthAttributeSet.h"
#include "GAS/AttributeSets/AirActionAttributeSet.h"
#include "GAS/AttributeSets/DashAttributeSet.h"
#include "GAS/AttributeSets/CMCAttributeSet.h"

// Gameplay tags
#include "GameplayTagContainer.h"

// Components
#include "Engine/DataTable.h"
#include "Components/CapsuleComponent.h"

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
	
	// Wall capsule detection
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Collision")
	UCapsuleComponent* WallCapsuleCollision;
	
	// Event handlers for overlap
	UFUNCTION()
	void OnWallCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnWallCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

	// Wall capsule offset radius
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Collision")
	float WallCapsuleDetectionOffsetRadius = 10.0f;

	// Get  Character Movement Component
	virtual UCharacterMovementComponent* ActorCharacterMovementComponent_Implementation() override;

	UFUNCTION(Category = "Input")
	virtual FVector GetMovementInput_Implementation() override;

	// Move
	virtual void CharacterMovementMove_Implementation(FVector MoveInput) override;

	// Jump
	virtual void CharacterMovementJump_Implementation() override;

	// Air Jump
	virtual void CharacterMovementAirJump_Implementation() override;

	// Wall running
	virtual void CharacterMovementCanStartWallRun_Implementation() override;
	virtual void CharacterMovementEndWallRun_Implementation() override;
	
	// Landed
	virtual void CharacterMovementLanded_Implementation() override;

	// Ground dash
	virtual void CharacterMovementGroundDash_Implementation() override;

	// Air dash
	virtual void CharacterMovementAirDash_Implementation() override;
	
	// IsAirborne
	virtual bool IsAirborne_Implementation() override;
	
protected:
	// Possessed by controller
	virtual void PossessedBy(AController* NewController) override;
	
	UFUNCTION()
	void BeginWallRun();

	UFUNCTION()
	void EndWallRun();
	
	// Called when the character lands
	virtual void Landed(const FHitResult& Hit) override;
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "GAS")
	TArray<TSubclassOf<UGameplayEffect>> OnLandedEffects;

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

	//* Health *//
	// Health attribute set
	UPROPERTY()
	UHealthAttributeSet* HealthAttributeSet;
	
	// Get current health
	UFUNCTION(BlueprintPure,
		Category = "Character|Health|")
	float GetCurrentHealth() const;

	// Get current health
	UFUNCTION(BlueprintPure,
		Category = "Character|Health|")
	float GetMaxHealth() const;

	//* Air Actions *//
	// AirAction attribute set
	UPROPERTY()
	UAirActionAttributeSet* AirActionAttributeSet;

	//* CMC *//
	// Character movement attribute set
	//* Health *//
	// Health attribute set
	UPROPERTY()
	UCMCAttributeSet* CMCAttributeSet;
	
	
	// Get current air actions
	UFUNCTION(BlueprintPure,
		Category = "Character|Actions|")
	float GetCurrentAirActions() const;

	// Get current air actions
	UFUNCTION(BlueprintPure,
		Category = "Character|Actions|")
	float GetMaxAirActions() const;

	//* Dash *//
	// Dash attribute set
	UPROPERTY()
	UDashAttributeSet* DashAttributeSet;
	
	// Grants initial attribute sets
	virtual void AddInitialCharacterAttributeSets();
	
	//* Data Tables *//
	UPROPERTY(BlueprintReadOnly,
		Category = "GAS")
	TObjectPtr<UDataTable> CharacterAttributeDataTable;

	//* Data Tables *//
	UPROPERTY(BlueprintReadOnly,
		Category = "GAS")
	TObjectPtr<UDataTable> CharacterMovementAttributeDataTable;

	void InitCharacterMovementComponent() const;

private:
	GENERATED_BODY()
};
