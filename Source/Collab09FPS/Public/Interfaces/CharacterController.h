// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "Character/CharacterBase.h"
#include "Weapon/WeaponBase.h"

#include "CharacterController.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UCharacterController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLAB09FPS_API ICharacterController
{
public:
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "HUD")
	void CharacterPossessed(ACharacterBase* Character);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Pawn")
	void PawnDeath();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Pawn")
	void WeaponSpawned(AWeaponBase* WeaponInstance);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Interactivity")
	void EnteredInteractZone(const FText& Message);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Interactivity")
	void LeftInteractZone();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Default")
	void OpenWeaponWheel();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Default")
	void CloseWeaponWheel();
	
protected:
private:
	GENERATED_BODY()
};
