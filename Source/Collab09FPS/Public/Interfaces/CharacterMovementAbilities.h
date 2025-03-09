// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Character/CharacterMovementComponentBase.h"
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
		Category = "Component")
	UCharacterMovementComponent* ActorCharacterMovementComponent();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Component")
	FVector GetMovementInput();
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Movement")
	void CharacterMovementJump();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Movement")
	void CharacterMovementAirJump();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Movement")
	void CharacterMovementGroundDash();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Movement")
	void CharacterMovementAirDash();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Movement")
	bool IsAirborne();
	
private:
	GENERATED_BODY()
};
