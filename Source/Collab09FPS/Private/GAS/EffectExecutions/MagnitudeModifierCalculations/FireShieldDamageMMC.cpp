// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/EffectExecutions/MagnitudeModifierCalculations/FireShieldDamageMMC.h"
#include "GAS/AttributeSets/HealthAttributeSet.h"

UFireShieldDamageMMC::UFireShieldDamageMMC()
{
	// Shield
	FireShieldDef.AttributeToCapture = UHealthAttributeSet::GetCurrentFireShieldAttribute();
	FireShieldDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	FireDamageDef.AttributeToCapture = UHealthAttributeSet::GetMetaElementalFireDamageAttribute();
	FireDamageDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	RelevantAttributesToCapture.Add(FireShieldDef);
	RelevantAttributesToCapture.Add(FireDamageDef);
}

float UFireShieldDamageMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Shield
	float FireShield = 0;
	GetCapturedAttributeMagnitude(FireShieldDef, Spec, EvaluationParameters, FireShield);

	// Damage
	float FireDamage = 0;
	GetCapturedAttributeMagnitude(FireDamageDef, Spec, EvaluationParameters, FireDamage);
	
	if (FireShield > 0)
	{
		// Add spec magnitude to damage
		FireDamage += Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Magnitude")),
		true, 0);
		return FireDamage;
	}
	else
	{
		return 0;
	}
}
