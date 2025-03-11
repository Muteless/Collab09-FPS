// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterMovementComponentBase.h"

#include "GameFramework/Character.h"
#include "Interfaces/CharacterMovementAbilities.h"


// Constructor
UCharacterMovementComponentBase::UCharacterMovementComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCharacterMovementComponentBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UCharacterMovementComponentBase::TickComponent(float DeltaTime, ELevelTick TickType,
													FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCharacterMovementComponentBase::PhysFlying(float deltaTime, int32 Iterations)
{
	PerformWallRun(deltaTime);
	Super::PhysFlying(deltaTime, Iterations);
}

void UCharacterMovementComponentBase::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	if (MovementMode == MOVE_Flying)
	{
		EnteredFlyingMovementMode();
	}
	
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
}

void UCharacterMovementComponentBase::EnteredFlyingMovementMode()
{
	// Entered wall running state
	// Interface with character to tell them they "landed"
	if (CharacterOwner->Implements<UCharacterMovementAbilities>())
	{
		ICharacterMovementAbilities::Execute_CharacterMovementLanded(CharacterOwner);
	}
}

bool UCharacterMovementComponentBase::CanWallRun() const
{
	FHitResult WallHit;
	return IsFalling() && Velocity.Length() > MinSpeedForWallRun;
}

void UCharacterMovementComponentBase::PerformWallRun(float DeltaTime)
{
	FHitResult WallHit;
	if (!IsWallDetected(WallHit))
	{
		EndWallRun(false);
		return;
	}
	
	// Get the direction in which the character should move along the wall
	FVector WallRunDirection = GetWallRunDirection(WallHit);
	
	CurrentWallNormal = WallHit.Normal; // Set current wall normal
	CurrentWallRunDirection = WallRunDirection; // Set current wall run direction
	
	// override velocity to follow the wall
	Velocity = WallRunDirection * MaxCustomMovementSpeed;
	Velocity += WallRunGravity;
	
	// Check if floor is detected (and within walkable distance)
	FFindFloorResult FloorResult;
	
	if (!InputDirectionWithinBounds())
	{
		EndWallRun(true);
		return;
	}

	FindFloor(UpdatedComponent->GetComponentLocation(), FloorResult, false);
	if (FloorResult.IsWalkableFloor())
	{
		EndWallRun(false);
		return;
	}
	
	// Rotate character to face wall direction
	if (!AlignedToWallRunDirection())
	{
		FRotator DesiredRotation = FRotationMatrix::MakeFromX(WallRunDirection).Rotator();
		FRotator CurrentRotation = CharacterOwner->GetActorRotation();
		FRotator SmoothedRotation = FMath::RInterpTo(CurrentRotation,
				DesiredRotation,
				DeltaTime,
				OntoWallRotationSpeed);
				CharacterOwner->SetActorRotation(SmoothedRotation);
	}
}

bool UCharacterMovementComponentBase::IsWallDetected(FHitResult& WallHit) const
{
	// Set up detection variables
	FVector UpperHitStart = CharacterOwner->GetActorLocation();
	UpperHitStart.Z += WallDetectionCapsuleHeight + 10;
	
	FVector LowerHitStart = CharacterOwner->GetActorLocation();
	LowerHitStart.Z -= WallDetectionCapsuleHeight + 10;

	// Collision query parameters
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(CharacterOwner); // Ignore the player character
	
	// Perform the capsule trace
	bool bUpperHit = GetWorld()->SweepSingleByChannel(
		WallHit,
		UpperHitStart,
		UpperHitStart,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeCapsule(WallDetectionCapsuleRadius,
			WallDetectionCapsuleHeight),
		QueryParams
	);

	// Perform the capsule trace
	bool bLowerHit = GetWorld()->SweepSingleByChannel(
		WallHit,
		LowerHitStart,
		LowerHitStart,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeCapsule(WallDetectionCapsuleRadius,
			WallDetectionCapsuleHeight),
		QueryParams
	);

	// Debug visualization for the capsule trace
	DrawDebugCapsule(
		GetWorld(),
		UpperHitStart,
		WallDetectionCapsuleHeight,
		WallDetectionCapsuleRadius,
		FQuat::Identity,
		bUpperHit ? FColor::Blue : FColor::Orange,
		false,
		1.0f
	);

	// Debug visualization for the capsule trace
	DrawDebugCapsule(
		GetWorld(),
		LowerHitStart,
		WallDetectionCapsuleHeight,
		WallDetectionCapsuleRadius,
		FQuat::Identity,
		bLowerHit ? FColor::Purple : FColor::Yellow,
		false,
		1.0f
	);

	if (bUpperHit && bLowerHit)
	{
		// Perform the capsule trace
		bool bHit = GetWorld()->SweepSingleByChannel(
			WallHit,
			CharacterOwner->GetActorLocation(),
			CharacterOwner->GetActorLocation(),
			FQuat::Identity,
			ECC_Visibility,
			FCollisionShape::MakeCapsule(WallDetectionCapsuleRadius,
				WallDetectionCapsuleHeight),
			QueryParams);
		return bHit; // Return true if a wall was detected
	}
	return false;
}

FVector UCharacterMovementComponentBase::GetWallRunDirection(const FHitResult& WallHit) const
{
	// Calculate the wall-running direction based on the wall's normal and the player's movement direction
	FVector WallNormal = WallHit.Normal;
	FVector Forward = CharacterOwner->GetActorForwardVector();

	// Project forward vector onto the wall surface
	FVector WallRunDirection = FVector::CrossProduct(WallNormal, FVector::UpVector);
	if (FVector::DotProduct(WallRunDirection, Forward) < 0.0f)
	{
		WallRunDirection *= -1.0f; // Ensure running along the correct direction
	}
	return WallRunDirection.GetSafeNormal();
}

bool UCharacterMovementComponentBase::AlignedToWallRunDirection() const
{
	return CharacterOwner->GetActorRotation() == FRotationMatrix::MakeFromX(CurrentWallRunDirection).Rotator();
}

bool UCharacterMovementComponentBase::InputDirectionWithinBounds() const
{
	FVector InputDirection = CharacterOwner->GetControlRotation().Vector();
	InputDirection.Z = 0; // Ignore vertical component
	InputDirection.Normalize();
	
	return FVector::DotProduct(CurrentWallRunDirection, InputDirection) >= 0.4f;
}

void UCharacterMovementComponentBase::ExitWallRunImpulse()
{
	FVector PushOffWallImpulseForce = FVector(CurrentWallNormal.X * EndWallRunOutImpulseStrength,
		CurrentWallNormal.Y * EndWallRunOutImpulseStrength,
		EndWallRunUpImpulseStrength);
	
	AddImpulse(PushOffWallImpulseForce, true);
}

void UCharacterMovementComponentBase::EndWallRun(const bool bPushOffWall)
{
	SetMovementMode(MOVE_Falling);
	
	if (bPushOffWall)
	{
		ExitWallRunImpulse();
	}
	
	// Reset wall-running variables
	CurrentWallNormal = FVector::ZeroVector;
	CurrentWallRunDirection = FVector::ZeroVector;
	
	// Exit wall-running mode
	if (CharacterOwner->Implements<UCharacterMovementAbilities>())
	{
		ICharacterMovementAbilities::Execute_CharacterMovementEndWallRun(CharacterOwner);
	}
}