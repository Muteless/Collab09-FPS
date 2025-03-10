// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/GAMovementBase.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Actor.h"

void UGAMovementBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData)
{
	// Ensure TriggerEventData is valid
	if (TriggerEventData)
	{
		if (TriggerEventData->TargetData.IsValid(0))
		{
			const FGameplayAbilityTargetDataHandle& TargetDataHandle = TriggerEventData->TargetData;
			if (TargetDataHandle.IsValid(0))
			{
				// Attempt FVector extraction from the target data
				const FHitResult* HitResult = TargetDataHandle.Get(0)->GetHitResult();;
				if (HitResult)
				{
					InputVector = HitResult->Location; // use location as input
				}
			}
		}
	}

	// call rest of activate ability
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
