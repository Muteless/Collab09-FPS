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
		Category = "Components")
	UCharacterMovementComponent* GetActorCharacterMovementComponent();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Movement")
	FVector GetMovementInput();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Movement")
	void CharacterMovementMove(FVector MoveInput);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Movement")
	void CharacterMovementWallRun();

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Movement")
	void CharacterMovementWallJump(FVector Direction, float Strength);
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Movement")
	void CharacterMovementEndWallRun();
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Movement")
	void CharacterMovementJump(FVector ForceDirection, float Strength, bool bSetZVelocityToZero);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "Movement")
	void CharacterMovementLanded();
	
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
