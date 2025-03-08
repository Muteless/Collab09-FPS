// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterMovementAbilities.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UCharacterMovementAbilities : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLAB09FPS_API ICharacterMovementAbilities
{
public:
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Input")
	void CharacterMovementJump();
	
private:
	GENERATED_BODY()
};
