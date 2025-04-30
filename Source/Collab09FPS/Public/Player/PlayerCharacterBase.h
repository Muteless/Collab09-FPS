// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"

// Interfaces
#include "Interfaces/SaveGameInterface.h"
#include "Interfaces/LoadInterface.h"

// Components
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon/WeaponBase.h"

// Persistent data
#include "PersistentData/PlayerSaveDataStruct.h"

// Attribute Sets
#include "GameFramework/SaveGame.h"
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
class COLLAB09FPS_API APlayerCharacterBase :
public ACharacterBase,
public ILoadInterface
{
public:
	// Sets default values for this character's properties
	APlayerCharacterBase();

	virtual void LoadData_Implementation(USaveGame* SaveGame) override;
	
	//* Stamina *//
	// Stamina attribute set
	UPROPERTY()
	UStaminaAttributeSet* StaminaAttributeSet;

	// Get current stamina
	UFUNCTION(BlueprintPure,
		Category = "Player|Stamina|")
	float GetCurrentStamina() const;

	FPlayerData MakePlayerSaveData();

protected:
	virtual void PossessedBy(AController* NewController) override;

	// Grants initial attribute sets
	virtual void AddInitialCharacterAttributeSets() override;

	UFUNCTION(BlueprintCallable)
	void SpawnWeapon();
	
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

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Category = "Camera")
	bool bInvertedYaw;
	
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Category = "Camera")
	bool bInvertedPitch;

private:
	GENERATED_BODY()
};
