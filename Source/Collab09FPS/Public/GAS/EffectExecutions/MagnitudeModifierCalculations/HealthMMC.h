// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "HealthMMC.generated.h"

/**
 * Class for calculating the magnitude of a gameplay effect related to health modification.
 */
UCLASS()
class COLLAB09FPS_API UHealthMMC : public UGameplayModMagnitudeCalculation
{
public:
	UHealthMMC();
	
	FGameplayEffectAttributeCaptureDefinition HealDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
protected:
private:
	GENERATED_BODY()
	
};
