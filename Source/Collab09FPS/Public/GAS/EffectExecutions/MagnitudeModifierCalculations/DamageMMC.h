// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "DamageMMC.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UDamageMMC : public UGameplayModMagnitudeCalculation
{
public:
	UDamageMMC();

	FGameplayEffectAttributeCaptureDefinition DamageDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
protected:
private:
	GENERATED_BODY()
	
};
