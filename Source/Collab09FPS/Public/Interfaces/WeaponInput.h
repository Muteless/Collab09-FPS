// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInput.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UWeaponInput : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLAB09FPS_API IWeaponInput
{
public:
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void WeaponFire();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void WeaponReload();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void WeaponReloadInterrupt();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void WeaponSwitch();
	
	UFUNCTION(BlueprintNativeEvent)
	bool GetWeaponMode();
	
private:
	GENERATED_BODY()
};
