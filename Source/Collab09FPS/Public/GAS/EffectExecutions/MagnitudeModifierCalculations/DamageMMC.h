// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "DamageMMC.generated.h"

/**
 * \class UDamageMMC
 *
 * \brief A class to calculate the magnitude of damage for gameplay effects.
 *
 * This class extends UGameplayModMagnitudeCalculation and provides implementation
 * for calculating the base magnitude of damage for gameplay effects.
 */
UCLASS()
class COLLAB09FPS_API UDamageMMC : public UGameplayModMagnitudeCalculation
{
public:
	UDamageMMC();
	
	FGameplayEffectAttributeCaptureDefinition DamageDef;
	
	FGameplayEffectAttributeCaptureDefinition FireShieldDef;
	FGameplayEffectAttributeCaptureDefinition CurseShieldDef;
	FGameplayEffectAttributeCaptureDefinition BloodShieldDef;
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
private:
	GENERATED_BODY()
	
};
