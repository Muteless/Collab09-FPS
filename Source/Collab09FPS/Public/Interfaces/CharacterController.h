// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Character/CharacterBase.h"
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
	
protected:
private:
	GENERATED_BODY()
};
