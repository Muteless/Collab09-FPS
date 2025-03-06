// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/MeleeAbilityBase.h"

#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "GAS/AbilitySystemComponentBase.h"


UMeleeAbilityBase::UMeleeAbilityBase()
{
	// Defaults
	MeleeDamage = 10.0f;
	MeleeRangeBox = FVector(100.0f, 100.0f, 100.0f);
	MeleeCollisionChannel = ECC_Pawn;
}

// Called when ability is activated
void UMeleeAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	// Get Avatar Actor
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!AvatarActor)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	// Get location and forward direction
	FVector StartLocation = AvatarActor->GetActorLocation();
	FVector ForwardVector = AvatarActor->GetActorForwardVector();
	FVector EndLocation = StartLocation + ForwardVector * MeleeRangeBox.X;

	// Perform box trace
	TArray<FHitResult> HitResults; // Stores results for all actors hit
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(AvatarActor); // Ignore the instigator itself
	
	// Box collision
	if (GetWorld()->SweepMultiByChannel(
		HitResults,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		MeleeCollisionChannel,
		FCollisionShape::MakeBox(FVector(
			MeleeRangeBox.X,
			MeleeRangeBox.Y,
			MeleeRangeBox.Z)),
		TraceParams))
	{
		// Iterate through each hit result
		for (const FHitResult& HitResult : HitResults)
		{
			if (const AActor* HitActor = HitResult.GetActor())
			{
				// Get ability system component (if it has one)
				if (UAbilitySystemComponentBase* TargetAsc = HitActor->FindComponentByClass<UAbilitySystemComponentBase>())
				{
					// Apply GameplayEffect to the target
					FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(HitEffect, 1.0f);
					TargetAsc->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
				}
			}
		}
	}

	// Debug: draw box collision
	DrawDebugBox(GetWorld(),
		StartLocation,
		FVector(MeleeRangeBox.X,
			MeleeRangeBox.Y,
			MeleeRangeBox.Z),
			FColor::Red,
			false,
			1,
			0,
			10);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
