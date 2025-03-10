// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GAMovementBase.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UGAMovementBase : public UGameplayAbility
{
public:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
protected:
	FVector InputVector;
private:
	GENERATED_BODY()
};
