// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"

// Interfaces
#include "Interfaces/CharacterInput.h"

// Components
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Weapon
#include "Weapon/WeaponBase.h"

// Attribute Sets
#include "GAS/AttributeSets/StaminaAttributeSet.h"

#include "PlayerCharacterBase.generated.h"

// Forward declarations
class UCameraComponent;
class USpringArmComponent;

/**
 * APlayerCharacterBase class represents the player-controlled character in the game.
 * It inherits from ACharacterBase and implements ICharacterInput.
 */

UCLASS()
class COLLAB09FPS_API APlayerCharacterBase : public ACharacterBase
{
public:
	// Sets default values for this character's properties
	APlayerCharacterBase();

	UFUNCTION(Category = "Input")
	virtual void InputActionLook_Implementation(EInputTypes InputType, FVector2D Input) override;

	//* Stamina *//
	// Stamina attribute set
	UPROPERTY()
	UStaminaAttributeSet* StaminaAttributeSet;

	// Get current stamina
	UFUNCTION(BlueprintPure,
		Category = "Player|Stamina|")
	float GetCurrentStamina() const;
	
	// Runs every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void PossessedBy(AController* NewController) override;

	// Grants initial attribute sets
	virtual void AddInitialCharacterAttributeSets() override;
	
	//* Camera *//
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Camera")
	UCameraComponent* CameraComponent;
	void UpdateFOVBasedOnSpeed(float DeltaTime) const;
	
	// Minimum FOV
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Category = "Camera|FOV")
	float FOVMinimum;

	// Maximum FOV
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Category = "Camera|FOV")
	float FOVMaximum;

	// Speed thresholds
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Camera|FOV")
	float MinFOVSpeedThreshold; // Speed at which FOV starts changing (e.g., idle speed)

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Camera|FOV")
	float MaxFOVSpeedThreshold; // Speed at which max FOV is reached (e.g., sprint speed)
	
	// FOV interpolation speed
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Camera|FOV")
	float FOVInterpSpeed;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Category = "Camera")
	bool bInvertedYaw;
	
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Category = "Camera")
	bool bInvertedPitch;

	// Spring Arm Component
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	//* Weapon *//
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Weapon | ")
	TSubclassOf<AWeaponBase> Weapon;

private:
	GENERATED_BODY()
};
