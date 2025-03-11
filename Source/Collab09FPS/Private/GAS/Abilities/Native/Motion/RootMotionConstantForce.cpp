// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Native/Motion/RootMotionConstantForce.h"
#include "GameFramework/CharacterMovementComponent.h"

URootMotionConstantForce::URootMotionConstantForce()
{
	// Define ability trigger for Gameplay Event
	// FAbilityTriggerData TriggerData;
	// TriggerData.TriggerTag = FGameplayTag::RequestGameplayTag(FName("Event.Native.RootMotionConstantForce"));
	// TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	//
	// AbilityTriggers.Add(TriggerData);
	
	Direction = FVector(0.0f, 0.0f, 0.0f);
	Strength = 0.0f;
	Duration = 0.0f;
	RootMotionSourceID = 0;
	AccumulateMode = ERootMotionAccumulateMode::Override;
}

void URootMotionConstantForce::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData)
{
	// If no event data, cancel the ability
	if (!TriggerEventData)
	{
		CancelAbility(Handle,
			ActorInfo,
			ActivationInfo, false);
		return;
	}
	
	// Actor is not valid
	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		CancelAbility(Handle,
			ActorInfo,
			ActivationInfo, false);
		return;
	}

	// Get Character and Movement component (assuming this is a character with a movement component)
	UCharacterMovementComponent* CharacterMovement = ActorInfo->AvatarActor->FindComponentByClass<UCharacterMovementComponent>();

	// If character movement component is not valid
	if (!CharacterMovement)
	{
		CancelAbility(Handle,
			ActorInfo,
			ActivationInfo, false);
		return;
	}

	// Create and initialize the root motion source
	TSharedPtr<FRootMotionSource_ConstantForce> RootMotionSource = MakeShared<FRootMotionSource_ConstantForce>();
	RootMotionSource->InstanceName = TEXT("RootMotionConstantForce");
	RootMotionSource->AccumulateMode = ERootMotionAccumulateMode::Override; // Override
	RootMotionSource->Priority = 100; // Priority is important!

	// Use parameters parsed from the Gameplay Event Data
	RootMotionSource->Force = Direction * Strength; // Apply force along vector
	RootMotionSource->Duration = Duration; // Duration of force application
	
	// Apply the root motion source
	RootMotionSourceID = CharacterMovement->ApplyRootMotionSource(RootMotionSource);

	// Automatically end the ability after root motion is applied
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void URootMotionConstantForce::CancelAbility(const FGameplayAbilitySpecHandle Handle,
											 const FGameplayAbilityActorInfo* ActorInfo, 
											 const FGameplayAbilityActivationInfo ActivationInfo,
											 bool bReplicateCancelAbility)
{
	// Remove the applied Root Motion Source if active
	if (ActorInfo && ActorInfo->AvatarActor.IsValid())
	{
		UCharacterMovementComponent* CharacterMovement = ActorInfo->AvatarActor->FindComponentByClass<UCharacterMovementComponent>();
		if (CharacterMovement && RootMotionSourceID != static_cast<uint16>(INDEX_NONE))
		{
			CharacterMovement->RemoveRootMotionSource(FName("RootMotionConstantForce"));
		}
	}

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}
