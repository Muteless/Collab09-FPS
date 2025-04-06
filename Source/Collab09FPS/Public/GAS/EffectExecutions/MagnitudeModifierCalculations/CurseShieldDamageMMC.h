// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "CurseShieldDamageMMC.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UCurseShieldDamageMMC : public UGameplayModMagnitudeCalculation
{
	UCurseShieldDamageMMC();

	FGameplayEffectAttributeCaptureDefinition CurseShieldDef;
	FGameplayEffectAttributeCaptureDefinition CurseDamageDef;

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
private:
	GENERATED_BODY()
};
