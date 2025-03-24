// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterBase.h"

#include "MeshPassProcessor.h"
#include "Collab09FPS/Collab09FPS.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Constructor
APlayerCharacterBase::APlayerCharacterBase()
{
	// CMC
	GetCharacterMovement()->SetActive(true);
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Create and configure a SpringArmComponent
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());  // Attach SpringArm to CapsuleComponent
	SpringArmComponent->TargetArmLength = 10.0f;						// Set the distance the camera will follow
	SpringArmComponent->bUsePawnControlRotation = true;					// Rotate arm based on controller movement
	SpringArmComponent->bDoCollisionTest = false;						// Don't want to collide with the arm
	SpringArmComponent->bEnableCameraLag = true;						// Enable camera lag
	SpringArmComponent->CameraLagSpeed = 5.0f;							// Set the camera lag speed

	// Create and configure the CameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);      // Attach the camera to the SpringArm
	CameraComponent->bUsePawnControlRotation = false;          // This disables direct control rotation, relying on spring arm

	// FOV
	FOVMinimum = 90;
	FOVMaximum = 110;
	MinFOVSpeedThreshold = 100.0f;
	MaxFOVSpeedThreshold = 1100.0f;
	FOVInterpSpeed = 5.0f;
	
	// Ensure the pawn itself doesn't rotate the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Attribute sets
	StaminaAttributeSet = CreateDefaultSubobject<UStaminaAttributeSet>(TEXT("Stamina Attribute Set"));
	
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APlayerCharacterBase::AddInitialCharacterAttributeSets()
{
	Super::AddInitialCharacterAttributeSets();
	
	if (AbilitySystemComponent)
	{
		// Stamina
		AbilitySystemComponent->AddSet<UStaminaAttributeSet>();
	}
}

// Tick
void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update FOV based on speed
	UpdateFOVBasedOnSpeed(DeltaTime);
}

// Camera
void APlayerCharacterBase::InputActionLook_Implementation(EInputTypes InputType, FVector2D Input)
{
	AddControllerYawInput(bInvertedYaw ? Input.X : -Input.X);
	AddControllerPitchInput(bInvertedPitch ? Input.Y : -Input.Y);
}

void APlayerCharacterBase::InputActionSwitchDimensions_Implementation(const EInputTypes InputType, const bool Input)
{
	switch (InputType)
	{
	case EInputTypes::Triggered:
		break;
	case EInputTypes::Started:
			// Switch dimensions
			if (AbilitySystemComponent)
			{
				// slide payload
				FGameplayEventData Payload;
					
				// start slide ability event
				AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Ability.SwitchDimensions")), &Payload);
				break;
			}
	case EInputTypes::Ongoing:
		break;
	case EInputTypes::Cancelled:
		break;
	case EInputTypes::Completed:
		break;
	}
}

void APlayerCharacterBase::UpdateFOVBasedOnSpeed(float DeltaTime) const
{
	float CurrentSpeed = GetVelocity().Size();

	// Ensure the camera component is valid
	if (!CameraComponent) return;
	
	// Map speed to FOV
	float TargetFOV = FMath::Lerp(FOVMinimum,
		FOVMaximum,
		FMath::Clamp((CurrentSpeed - MinFOVSpeedThreshold) / (MaxFOVSpeedThreshold - MinFOVSpeedThreshold),
			0.0f,
			1.0f));

	float CurrentFOV = CameraComponent->FieldOfView;
	CameraComponent->FieldOfView = FMath::FInterpTo(CurrentFOV,
		TargetFOV,
		DeltaTime,
		FOVInterpSpeed);
}

//* Blueprint Helper functions *//
// Get current stamina attribute
float APlayerCharacterBase::GetCurrentStamina() const
{
	if (StaminaAttributeSet)
	{
		return StaminaAttributeSet->GetCurrentStamina();
	}
	return -1.0f;
}