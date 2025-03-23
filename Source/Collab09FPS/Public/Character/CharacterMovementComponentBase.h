// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterMovementComponentBase.generated.h"

/**
 * @class UCharacterMovementComponentBase
 * @brief A custom character movement component that extends functionality with features like wall-running and custom flying physics.
 *
 * This class derives from UCharacterMovementComponent and provides additional movement behavior such as wall-running and the ability
 * to customize flying physics.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COLLAB09FPS_API UCharacterMovementComponentBase : public UCharacterMovementComponent
{
public:
	// Sets default values for this component's properties
	UCharacterMovementComponentBase();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	// Called every physics tick
	virtual void PhysFlying(float deltaTime,
		int32 Iterations) override;

	// respond to movement mode changes
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode,
		uint8 PreviousCustomMode) override;
	
	virtual void EnteredFlyingMovementMode();
	virtual void EnteredCustomMovementMode();

#pragma region Wall Running
	
	// Wall running
	bool IsWallDetected(FHitResult& WallHit) const;
	void PerformWallRun(float DeltaTime);
	bool bExitWallRun = false;
	void ExitWallRunImpulse();
	FVector CurrentWallNormal;
	
	FVector GetWallRunDirection(const FHitResult& WallHit) const;
	FVector CurrentWallRunDirection;
	bool InputDirectionWithinBounds() const;
	bool AlignedToWallRunDirection() const;
	
	void EndWallRun(const bool bPushOffWall);
	
	UFUNCTION(BlueprintPure,
		Category = "WallRunning")
	bool CanWallRun() const;

	// Strength of the impulse applied to the character outwards when transitioning off a wall-run
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "WallRunning")
	float EndWallRunOutImpulseStrength = 900.0f;
	
	// Strength of the impulse applied to the character upwards when transitioning off a wall-run
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "WallRunning")
	float EndWallRunUpImpulseStrength = 900.0f;

#pragma endregion Wall Running

#pragma region Sliding
	
	// Sliding
	bool CanSlide();
	bool bWantsToSlide;
	void StartSliding();
	void Sliding();
	void CallToStopSliding();
	void StopSliding();
	FVector CurrentSlideDirection;

	// Constant speed applied when sliding
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Sliding")
	float SlideSpeed = 1400;

#pragma endregion Sliding
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Wall-run settings

	// Minimum speed required for the character to initiate a wall-run
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "WallRunning")
	float MinSpeedForWallRun = 100.f;

	// Radius of the capsule used to detect nearby walls for wall-running
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "WallRunning")
	float WallDetectionCapsuleRadius = 54.0f;

	// Half-height of the capsule used to detect nearby walls for wall-running
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "WallRunning")
	float WallDetectionCapsuleHeight = 54.0f;

	// Gravity scale applied to the character while wall-running
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "WallRunning")
	FVector WallRunGravity = FVector(0.0f, 0.0f, -60.0f);

	// Speed at which the character rotates to align with the wall during wall-run initiation
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "WallRunning")
	float OntoWallRotationSpeed = 10.0f;

private:
	GENERATED_BODY()
};
