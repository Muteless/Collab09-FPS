// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Native/Motion/KnockbackForce.h"

UKnockbackForce::UKnockbackForce()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Effect.Native.KnockbackForce")));
	
	// Define ability trigger for Gameplay Event
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = FGameplayTag::RequestGameplayTag(FName("Event.Native.KnockbackForce"));
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	
	AbilityTriggers.Add(TriggerData);
}

void UKnockbackForce::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Strength = TriggerEventData->EventMagnitude;
	Direction = FVector(ActorInfo->AvatarActor->GetActorForwardVector().X * -1,
						ActorInfo->AvatarActor->GetActorForwardVector().Y * -1,
						0.1);
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UKnockbackForce::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}
