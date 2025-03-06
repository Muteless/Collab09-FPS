// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterBase.h"

#include "Collab09FPS/Collab09FPS.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacterBase::APlayerCharacterBase()
{
	// Initialize the CMC
	CharacterMovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("Character Movement Component"));
	
	// Initialize the Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	
	// Attribute sets
	StaminaAttributeSet = CreateDefaultSubobject<UStaminaAttributeSet>(TEXT("Stamina Attribute Set"));
}

void APlayerCharacterBase::InputActionMove_Implementation(const EInputTypes InputType, const FVector2D Input)
{
	ICharacterInput::InputActionMove_Implementation(InputType, Input);

	switch (InputType)
	{
		case EInputTypes::Triggered:
			MoveTriggered(Input);
	}
	return;
}

// Movement
void APlayerCharacterBase::MoveTriggered(const FVector2d Input)
{
	AddMovementInput(GetActorForwardVector(), Input.Y, false);
	AddMovementInput(GetActorRightVector(), Input.X, false);
	return;
}

void APlayerCharacterBase::InputActionLook_Implementation(EInputTypes InputType, FVector2D Input)
{
	ICharacterInput::InputActionLook_Implementation(InputType, Input);
	return;
}

// Called to bind functionality to input
void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Get current stamina attribute
float APlayerCharacterBase::GetCurrentStamina() const
{
	if (StaminaAttributeSet)
	{
		return StaminaAttributeSet->GetCurrentStamina();
	}
	return 0.0f;
}