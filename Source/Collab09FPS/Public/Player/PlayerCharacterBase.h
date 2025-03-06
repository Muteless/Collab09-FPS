// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"

// Attributes
#include "GAS/AttributeSets/StaminaAttributeSet.h"

// Interfaces
#include "Interfaces/CharacterInput.h"

// Components
#include "Camera/CameraComponent.h"

#include "PlayerCharacterBase.generated.h"

UCLASS()
class COLLAB09FPS_API APlayerCharacterBase : public ACharacterBase, public ICharacterInput
{
public:
	// Sets default values for this character's properties
	APlayerCharacterBase();

	// Input
	UFUNCTION(Category = "Input")
	virtual void InputActionMove_Implementation(EInputTypes InputType, FVector2D Input) override;

	UFUNCTION(Category = "Input")
	virtual void InputActionLook_Implementation(EInputTypes InputType, FVector2D Input) override;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera component
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Player | Camera | ")
	UCameraComponent* CameraComponent;

	// CMC component
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Player | Camera | ")
	UCharacterMovementComponent* CharacterMovementComponent;

	void MoveTriggered(FVector2d Input);
	
	//* Stamina *//
	// Stamina attribute set
	UPROPERTY()
	UStaminaAttributeSet* StaminaAttributeSet;

	// Get current stamina
	UFUNCTION(BlueprintPure,
		Category = "Player | Stamina | ")
	float GetCurrentStamina() const;

private:
	GENERATED_BODY()
};
