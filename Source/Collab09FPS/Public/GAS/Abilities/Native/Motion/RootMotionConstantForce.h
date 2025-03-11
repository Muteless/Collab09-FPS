// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/RootMotionSource.h"
#include "GAS/Abilities/Native/NativeGameplayAbility.h"
#include "RootMotionConstantForce.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class COLLAB09FPS_API URootMotionConstantForce : public UNativeGameplayAbility
{
public:
	URootMotionConstantForce();
	
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

	UPROPERTY()
	uint16 RootMotionSourceID;

	// Direction of force applied (FHit Normal)
	UPROPERTY(BlueprintReadWrite)
	FVector Direction;

	// Strength of force applied (FHit Distance)
	UPROPERTY(BlueprintReadWrite)
	float Strength;

	// Duration of force applied (FHit Time)
	UPROPERTY(BlueprintReadWrite)
	float Duration;

	UPROPERTY(BlueprintReadWrite)
	ERootMotionAccumulateMode AccumulateMode;

protected:
private:
	GENERATED_BODY()
};
