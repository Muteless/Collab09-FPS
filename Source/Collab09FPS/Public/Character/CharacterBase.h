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

// Gameplay tags
#include "GameplayTagContainer.h"

// Components
#include "Engine/DataTable.h"
#include "Components/CapsuleComponent.h"
#include "Weapon/WeaponBase.h"

// Interfaces
#include "Interfaces/MovementComponentAttributeUpdate.h"
#include "Interfaces/CharacterMovementAbilities.h"
#include "Interfaces/CharacterInput.h"

// Structs
#include "Collab09FPS/Collab09FPS.h"
#include "Interfaces/MovementComponentAttributeUpdate.h"

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
public ICharacterInput,
public IAbilitySystemInterface,
public ICharacterMovementAbilities,
public IMovementComponentAttributeUpdate
{
public:
	// Sets default values for this character's properties
	ACharacterBase();

	// Input
	UFUNCTION(Category = "Input")
	virtual void InputActionMove_Implementation(EInputTypes InputType, FVector2D Input) override;
	
	UFUNCTION(Category = "Input")
	virtual void InputActionJump_Implementation(EInputTypes InputType, bool Input) override;

	UFUNCTION(Category = "Input")
	virtual void InputActionDash_Implementation(const EInputTypes InputType, const bool Input) override;

	UFUNCTION(Category = "Input")
	virtual void InputActionSlide_Implementation(const EInputTypes InputType, const bool Input) override;
	
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

	// Get Character Movement Component
	virtual UCharacterMovementComponent* GetActorCharacterMovementComponent_Implementation() override;
	
#pragma region CMCAttributeSetChanges
	
	virtual void SetCMCMaxWalkSpeed_Implementation(float MaxWalkSpeed) override;
	virtual void SetCMCMaxAcceleration_Implementation(float MaxAcceleration) override;
	virtual void SetCMCGravityScale_Implementation(float GravityScale) override;
	virtual void SetCMCMaxWallRunSpeed_Implementation(float MaxWallRunSpeed) override;
	virtual void SetCMCPushOffWallHorizontalSpeed_Implementation(float PushOffWallHorizontalSpeed) override;
	virtual void SetCMCPushOffWallVerticalSpeed_Implementation(float PushOffWallVerticalSpeed) override;
	virtual void SetCMCGroundFriction_Implementation(float GroundFriction) override;
	virtual void SetCMCBrakingFriction_Implementation(float BrakingFriction) override;
	
#pragma endregion CMCAttributeSetChanges

	UFUNCTION(Category = "Input")
	virtual FVector GetMovementInput_Implementation() override;

	
#pragma region Actions
	
	// Move
	virtual void CharacterMovementMove_Implementation(FVector MoveInput) override;

	// Jump
	virtual void CharacterMovementJump_Implementation(FVector ForceDirection, float Strength, bool bSetZVelocityToZero) override;

	// Air Jump
	virtual void CharacterMovementAirJump_Implementation() override;

	// Wall running
	virtual void CharacterMovementWallRun_Implementation() override;
	virtual void CharacterMovementWallJump_Implementation(FVector Direction, float Strength) override;
	virtual void CharacterMovementEndWallRun_Implementation() override;
	
	// Landed
	virtual void CharacterMovementLanded_Implementation() override;

	// Ground dash
	virtual void CharacterMovementGroundDash_Implementation() override;

	// Air dash
	virtual void CharacterMovementAirDash_Implementation() override;
	
	// IsAirborne
	virtual bool IsAirborne_Implementation() override;

#pragma endregion Actions
	
protected:
	// Possessed by controller
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void Landed(const FHitResult& Hit) override;
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "GAS")
	TArray<TSubclassOf<UGameplayEffect>> OnLandedEffects;

	UPROPERTY(VisibleAnywhere,
		BlueprintReadWrite)
	USceneComponent* WeaponLocation;
	
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite)
	TSubclassOf<AWeaponBase> WeaponClass;
	UPROPERTY(BlueprintReadOnly)
	AWeaponBase* WeaponInstance;
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite)
	FName WeaponSocketName;
	
	UFUNCTION(BlueprintCallable)
	void SpawnWeapon();

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
	
	// Get current air actions
	UFUNCTION(BlueprintPure,
		Category = "Character|Actions|")
	float GetCurrentAirActions() const;

	// Get current air actions
	UFUNCTION(BlueprintPure,
		Category = "Character|Actions|")
	float GetMaxAirActions() const;

	//* CMC *//
	// Character Movement attribute set
	UPROPERTY()
	UCMCAttributeSet* CMCAttributeSet;
	
	//* Dash *//
	// Dash attribute set
	UPROPERTY()
	UDashAttributeSet* DashAttributeSet;

	//* Meta Effects *//
	// Meta effects attribute aet
	UPROPERTY()
	UMetaEffectsAttributeSet* MetaEffectsAttributeSet;
	
	// Grants initial attribute sets
	virtual void AddInitialCharacterAttributeSets();

private:
	GENERATED_BODY()
};
