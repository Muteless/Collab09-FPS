// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RootMotionConstantForce.h"
#include "KnockbackForce.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UKnockbackForce : public URootMotionConstantForce
{
	UKnockbackForce();
	
	// Override Activate Ability
	virtual void ActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData) override;

	// Override Cancel Ability
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateCancelAbility) override;
	
private:
	GENERATED_BODY()
};
