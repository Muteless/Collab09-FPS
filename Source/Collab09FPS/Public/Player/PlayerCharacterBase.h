// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"

// Interfaces
#include "Interfaces/CharacterInput.h"
#include "Interfaces/SaveGameInterface.h"

// Components
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Attribute Sets
#include "GameFramework/SaveGame.h"
#include "GAS/AttributeSets/StaminaAttributeSet.h"
#include "Interfaces/SaveGameInterface.h"

#include "PlayerCharacterBase.generated.h"

// Forward declarations
class UCameraComponent;
class USpringArmComponent;

/**
 * APlayerCharacterBase class represents the player-controlled character in the game.
 * It inherits from ACharacterBase and implements ICharacterInput.
 */

UCLASS()
class COLLAB09FPS_API APlayerCharacterBase :
public ACharacterBase,
public ISaveGameInterface
{
public:
	// Sets default values for this character's properties
	APlayerCharacterBase();

	virtual void LoadData_Implementation(USaveGame* SaveGame);

	#pragma region Input
	
	UFUNCTION(Category = "Input")
	virtual void InputActionLook_Implementation(EInputTypes InputType, FVector2D Input) override;

	UFUNCTION(Category = "Input")
	virtual void InputActionSwitchDimensions_Implementation(const EInputTypes InputType, const bool Input) override;
	
	// Wall capsule detection
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Collision")
	UCapsuleComponent* WallCapsuleCollision;

	#pragma endregion Input
	
	// Event handlers for overlap
	UFUNCTION()
	void OnWallCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnWallCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	// Wall capsule offset radius
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Collision")
	float WallCapsuleDetectionOffsetRadius = 10.0f;

	#pragma region CMCAttributeChanges
	
	virtual void SetCMCMaxWallRunSpeed_Implementation(float MaxWallRunSpeed) override;
	virtual void SetCMCPushOffWallHorizontalSpeed_Implementation(float PushOffWallHorizontalSpeed) override;
	virtual void SetCMCPushOffWallVerticalSpeed_Implementation(float PushOffWallVerticalSpeed) override;

	#pragma endregion CMCAttributeChanges
	
	// Wall running
	virtual void CharacterMovementWallRun_Implementation() override;
	virtual void CharacterMovementWallJump_Implementation(FVector Direction, float Strength) override;
	virtual void CharacterMovementEndWallRun_Implementation() override;
	
	//* Stamina *//
	// Stamina attribute set
	UPROPERTY()
	UStaminaAttributeSet* StaminaAttributeSet;

	// Get current stamina
	UFUNCTION(BlueprintPure,
		Category = "Player|Stamina|")
	float GetCurrentStamina() const;
	
	// Runs every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void PossessedBy(AController* NewController) override;

	// Grants initial attribute sets
	virtual void AddInitialCharacterAttributeSets() override;
	
	//* Camera *//
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Camera")
	UCameraComponent* CameraComponent;
	void UpdateFOVBasedOnSpeed(float DeltaTime) const;
	
	// Minimum FOV
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Category = "Camera|FOV")
	float FOVMinimum;

	// Maximum FOV
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Category = "Camera|FOV")
	float FOVMaximum;

	// Speed thresholds
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Camera|FOV")
	float MinFOVSpeedThreshold; // Speed at which FOV starts changing (e.g., idle speed)

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Camera|FOV")
	float MaxFOVSpeedThreshold; // Speed at which max FOV is reached (e.g., sprint speed)
	
	// FOV interpolation speed
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Camera|FOV")
	float FOVInterpSpeed;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Category = "Camera")
	bool bInvertedYaw;
	
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Category = "Camera")
	bool bInvertedPitch;

	// Spring Arm Component
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Camera")
	USpringArmComponent* SpringArmComponent;

private:
	GENERATED_BODY()
};
