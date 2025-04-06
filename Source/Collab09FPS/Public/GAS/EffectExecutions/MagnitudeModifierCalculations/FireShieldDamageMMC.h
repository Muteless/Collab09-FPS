// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "FireShieldDamageMMC.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UFireShieldDamageMMC : public UGameplayModMagnitudeCalculation
{
public:
	UFireShieldDamageMMC();

	FGameplayEffectAttributeCaptureDefinition FireShieldDef;
	FGameplayEffectAttributeCaptureDefinition FireDamageDef;

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
private:
	GENERATED_BODY()
};
