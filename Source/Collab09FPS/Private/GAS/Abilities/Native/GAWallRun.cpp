// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Native/GAWallRun.h"
#include "Interfaces/CharacterMovementAbilities.h"

#include "Chaos/Utilities.h"

void UGAWallRun::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                 const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                 const FGameplayEventData* TriggerEventData)
{
	// Always call the parent function
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Ensure TriggerEventData is valid
	if (TriggerEventData)
	{
		// Extract the HitResult
		FHitResult HitResult = *TriggerEventData->TargetData.Get(0)->GetHitResult();

		// If the character can run
		if (CanWallRun(ActorInfo, HitResult))
		{
			// Begin wall run using the HitResult
			BeginWallRun(ActorInfo, HitResult); // Pass the HitResult
			return;
		}
	}
}

bool UGAWallRun::IsWallDetected(const FGameplayAbilityActorInfo* ActorInfo, FHitResult& HitResult) const
{
	AActor* Character = ActorInfo->AvatarActor.Get();
	
	// Set up detection variables
	FVector UpperHitStart = Character->GetActorLocation();
	UpperHitStart.Z += UpperWallDetectionCapsuleHeight + 10;
	
	FVector LowerHitStart = Character->GetActorLocation();
	LowerHitStart.Z -= LowerWallDetectionCapsuleHeight + 10;

	// Collision query parameters
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Character); // Ignore the player character
	
	// Perform the upper capsule trace
	bool bUpperHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		UpperHitStart,
		UpperHitStart,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeCapsule(UpperWallDetectionCapsuleRadius,
			UpperWallDetectionCapsuleHeight),
		QueryParams
	);

	// Perform the lower capsule trace
	bool bLowerHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		LowerHitStart,
		LowerHitStart,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeCapsule(LowerWallDetectionCapsuleRadius,
			LowerWallDetectionCapsuleHeight),
		QueryParams
	);

	// Debug visualization for the capsule trace
	DrawDebugCapsule(
		GetWorld(),
		UpperHitStart,
		UpperWallDetectionCapsuleHeight,
		UpperWallDetectionCapsuleRadius,
		FQuat::Identity,
		bUpperHit ? FColor::Blue : FColor::Orange,
		false,
		1.0f
	);

	// Debug visualization for the capsule trace
	DrawDebugCapsule(
		GetWorld(),
		LowerHitStart,
		UpperWallDetectionCapsuleHeight,
		UpperWallDetectionCapsuleRadius,
		FQuat::Identity,
		bLowerHit ? FColor::Purple : FColor::Yellow,
		false,
		1.0f
	);

	if (bUpperHit && bLowerHit)
	{
		// Perform the capsule trace
		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			Character->GetActorLocation(),
			Character->GetActorLocation(),
			FQuat::Identity,
			ECC_Visibility,
			FCollisionShape::MakeCapsule(UpperWallDetectionCapsuleRadius,
				UpperWallDetectionCapsuleHeight),
			QueryParams);
		return bHit; // Return true if a wall was detected
	}
	return false;
}

bool UGAWallRun::CanWallRun(const FGameplayAbilityActorInfo* ActorInfo, FHitResult& HitResult)
{
	// Normalize vectors
	FVector NormalizedPlayerForward = ActorInfo->AvatarActor->GetActorForwardVector().GetSafeNormal();
	FVector NormalizedWallNormal = HitResult.Normal.GetSafeNormal();
	
	// Calculate the dot product
	float Dot = FVector::DotProduct(NormalizedPlayerForward, NormalizedWallNormal);

	// Player angle is within acceptable range
	if (FMath::Abs(Dot) > MinimumWallFacingThreshold && Dot < MaximumWallFacingThreshold)
	{
		if (IsWallDetected(ActorInfo, HitResult))
		{
			return true;
		}
		return false;
	}
	return false;
}


void UGAWallRun::BeginWallRun(const FGameplayAbilityActorInfo* ActorInfo, FHitResult& HitResult)
{
	PerformWallRun(ActorInfo, HitResult);
	// if (ActorInfo && ActorInfo->AvatarActor.IsValid())
	// {
	// 	ICharacterMovementAbilities::Execute_CharacterMovementWallRun(ActorInfo->AvatarActor.Get());
	// }
}

void UGAWallRun::PerformWallRun(const FGameplayAbilityActorInfo* ActorInfo, FHitResult& HitResult)
{
	
}

void UGAWallRun::EndWallRun()
{
	
}

void UGAWallRun::EndAbility(const FGameplayAbilitySpecHandle Handle,
                            const FGameplayAbilityActorInfo* ActorInfo,
                            const FGameplayAbilityActivationInfo ActivationInfo,
                            bool bReplicateEndAbility,
                            bool bWasCancelled)
{
	
}


