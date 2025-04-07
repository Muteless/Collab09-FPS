// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
public:
	UDamageExecutionCalculation();

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
private:
	// Health
	const FGameplayEffectAttributeCaptureDefinition HealthDef;
	
	// Damage
	const FGameplayEffectAttributeCaptureDefinition DamageDef;

	// Shield
	const FGameplayEffectAttributeCaptureDefinition FireShieldDef;
	const FGameplayEffectAttributeCaptureDefinition CurseShieldDef;
	const FGameplayEffectAttributeCaptureDefinition BloodShieldDef;
	
	GENERATED_BODY()
};
