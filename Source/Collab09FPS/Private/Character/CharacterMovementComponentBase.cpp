// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterMovementComponentBase.h"

#include "GameFramework/Character.h"


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

	if (MovementMode == MOVE_Custom && CustomMovementMode == MOVE_WallRunning)
	{
		// Perform wall running
		PerformWallRun(DeltaTime);
	}
}

bool UCharacterMovementComponentBase::CanWallRun() const
{
	return IsFalling() && Velocity.Size() > MinimumWallRunEntrySpeed;
}

void UCharacterMovementComponentBase::PerformWallRun(float DeltaTime)
{
	FHitResult WallHit;
	if (IsWallDetected(WallHit) && CharacterOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wall detected!"));
		// Get the direction in which the character should move along the wall
		FVector WallRunDirection = GetWallRunDirection(WallHit);

		// Adjust velocity to make the character run along the wall
		Velocity = WallRunDirection * WallRunSpeed;

		// Reduce gravity
		GravityScale = WallRunGravityScale;

		// Align character's rotation with the wall
		CharacterOwner->SetActorRotation(FRotationMatrix::MakeFromX(WallRunDirection).Rotator());
	}
	else
	{
		// Fall back to "falling" (no pun intended) if no wall is detected
		SetMovementMode(MOVE_Falling);
	}
}

bool UCharacterMovementComponentBase::IsWallDetected(FHitResult& WallHit) const
{
	FVector Start = CharacterOwner->GetActorLocation();
	FVector Forward = CharacterOwner->GetActorForwardVector();
	FVector End = Start + Forward * WallDetectionRange;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(CharacterOwner);

	// TODO: Capsule trace INSTEAD 
	return GetWorld()->LineTraceSingleByChannel(WallHit, Start, End, ECC_Visibility, QueryParams);
}

FVector UCharacterMovementComponentBase::GetWallRunDirection(const FHitResult& WallHit) const
{
	// Calculate the wall-running direction based on the wall's normal and the player's movement direction
	FVector WallNormal = WallHit.ImpactNormal;
	FVector Forward = CharacterOwner->GetActorForwardVector();

	// Project forward vector onto the wall surface
	FVector WallRunDirection = FVector::CrossProduct(WallNormal, FVector::UpVector);
	if (FVector::DotProduct(WallRunDirection, Forward) < 0.0f)
	{
		WallRunDirection *= -1.0f; // Ensure running along the correct side
	}
	
	return WallRunDirection.GetSafeNormal();
}