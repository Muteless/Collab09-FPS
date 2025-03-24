// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterMovementComponentBase.h"

#include "GameFramework/Character.h"
#include "Interfaces/CharacterMovementAbilities.h"
#include "AbilitySystemComponent.h"


// Constructor
UCharacterMovementComponentBase::UCharacterMovementComponentBase()
{
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
	if (bWantsToSlide)
	{
		Sliding();
	}
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCharacterMovementComponentBase::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	if (MovementMode == MOVE_Flying)
	{
		EnteredFlyingMovementMode();
	}
	
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
}

void UCharacterMovementComponentBase::EnteredCustomMovementMode()
{
	if (GetPawnOwner()->GetLastMovementInputVector() == FVector::ZeroVector)
	{
		CurrentSlideDirection = FVector(GetPawnOwner()->GetActorForwardVector().X,
			GetPawnOwner()->GetActorForwardVector().Y,
			0);
	}
	else
	{
		CurrentSlideDirection = FVector(GetPawnOwner()->GetLastMovementInputVector().X,
			GetPawnOwner()->GetLastMovementInputVector().Y,
			0);
	}
}

#pragma region WallRun

void UCharacterMovementComponentBase::PhysFlying(float deltaTime, int32 Iterations)
{
	PerformWallRun(deltaTime);
	Super::PhysFlying(deltaTime, Iterations);
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
	return IsFalling() && Velocity.Length() > MinSpeedForWallRun;
}

void UCharacterMovementComponentBase::PerformWallRun(float DeltaTime)
{
	if (Velocity.Size() <= MinSpeedForWallRun)
	{
		EndWallRun(false);
		return;
	}
	
	if (bExitWallRun)
	{
		EndWallRun(true);
		return;
	}
	
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
	
	if (!InputDirectionWithinBounds())
	{
		EndWallRun(true);
		return;
	}
	
	// Check if floor is detected (and within walkable distance)
	FFindFloorResult FloorResult;
	
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
	bExitWallRun = false;
}

#pragma endregion WallRun

#pragma region Sliding

// todo: make it so a player can not keep sliding when their velocity is zero
// todo: and yes, this function doesnt do anything rn //dan @_@
bool UCharacterMovementComponentBase::CanSlide()
{
	return true;
}


void UCharacterMovementComponentBase::StartSliding()
{
	if (!CanSlide())
	{
		CallToStopSliding();
	}
	
	if (GetLastInputVector() == FVector::Zero())
	{
		CurrentSlideDirection = FVector(GetPawnOwner()->GetActorForwardVector().X,
			GetPawnOwner()->GetActorForwardVector().Y,
			0).GetSafeNormal2D();
	}
	else
	{
		CurrentSlideDirection = FVector(GetLastInputVector().X,
			GetLastInputVector().Y,
			0).GetSafeNormal2D();
	}

	bWantsToSlide = true;
	bWantsToCrouch = true;
	Crouch();
}

void UCharacterMovementComponentBase::Sliding()
{
	FVector CurrentVelocity = CurrentSlideDirection * SlideSpeed;
	CurrentVelocity *= GetWorld()->GetDeltaSeconds();
	
	FRotator CurrentRotation = FRotator(0, GetPawnOwner()->GetControlRotation().Yaw, 0);
	
	FHitResult HitResult;
	SafeMoveUpdatedComponent(CurrentVelocity, CurrentRotation, true, HitResult, ETeleportType::None);
}

void UCharacterMovementComponentBase::CallToStopSliding()
{
	if (CharacterOwner)
	{
		if (UAbilitySystemComponent* AbilitySystem = CharacterOwner->FindComponentByClass<UAbilitySystemComponent>())
		{
			FGameplayEventData Payload;
			AbilitySystem->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(TEXT("Event.Ability.StopSlide")), &Payload);
		}
	}
}

void UCharacterMovementComponentBase::StopSliding()
{
	bWantsToSlide = false;
	bWantsToCrouch = false;
	UnCrouch();
}

#pragma endregion Sliding