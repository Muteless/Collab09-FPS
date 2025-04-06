// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "BloodShieldDamageMMC.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UBloodShieldDamageMMC : public UGameplayModMagnitudeCalculation
{
public:
	UBloodShieldDamageMMC();

	FGameplayEffectAttributeCaptureDefinition BloodShieldDef;
	FGameplayEffectAttributeCaptureDefinition BloodDamageDef;

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
private:
	GENERATED_BODY()
};
