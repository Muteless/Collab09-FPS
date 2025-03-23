// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Collab09FPS/Collab09FPS.h"

#include "CharacterInput.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UCharacterInput : public UInterface
{
	GENERATED_BODY()
};

/**
 * @class ICharacterInput
 *
 * Interface that defines character input actions. This interface is intended to be implemented
 * by classes that require handling character-specific input actions, such as movement, looking,
 * and various gameplay actions.
 */

class COLLAB09FPS_API ICharacterInput
{
public:
	// Input actions
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Input")
	void InputActionMove(const EInputTypes InputType, const FVector2D Input);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Input")
	void InputActionLook(const EInputTypes InputType, const FVector2D Input);
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Input")
	void InputActionPrimaryAction(const EInputTypes InputType, const bool Input);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Input")
	void InputActionSecondaryAction(const EInputTypes InputType, const bool Input);
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Input")
	void InputActionJump(const EInputTypes InputType, const bool Input);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Input")
	void InputActionDash(const EInputTypes InputType, const bool Input);
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Input")
	void InputActionSlide(const EInputTypes InputType, const bool Input);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Input")
	void InputActionReload(const EInputTypes InputType, const bool Input);
	
private:
	GENERATED_BODY()
};
