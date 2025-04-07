// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ShieldDamageExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UShieldDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
public:
	UShieldDamageExecutionCalculation();

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
private:
	// Damage
	const FGameplayEffectAttributeCaptureDefinition FireDamageDef;
	const FGameplayEffectAttributeCaptureDefinition CurseDamageDef;
	const FGameplayEffectAttributeCaptureDefinition BloodDamageDef;

	// Shield
	const FGameplayEffectAttributeCaptureDefinition FireShieldDef;
	const FGameplayEffectAttributeCaptureDefinition CurseShieldDef;
	const FGameplayEffectAttributeCaptureDefinition BloodShieldDef;
	
	GENERATED_BODY()
};
