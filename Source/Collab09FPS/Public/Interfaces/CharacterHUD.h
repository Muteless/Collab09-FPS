// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterHUD.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UCharacterHUD : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLAB09FPS_API ICharacterHUD
{
public:
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "HUD")
	void CreateHUD(const ACharacterBase* Character);
protected:
	
private:
	GENERATED_BODY()
	
};
