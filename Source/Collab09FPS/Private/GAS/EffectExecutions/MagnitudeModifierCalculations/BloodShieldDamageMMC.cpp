// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/EffectExecutions/MagnitudeModifierCalculations/BloodShieldDamageMMC.h"
#include "GAS/AttributeSets/HealthAttributeSet.h"

UBloodShieldDamageMMC::UBloodShieldDamageMMC()
{
	// Shield
	BloodShieldDef.AttributeToCapture = UHealthAttributeSet::GetCurrentBloodShieldAttribute();
	BloodShieldDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	// Damage
	BloodDamageDef.AttributeToCapture = UHealthAttributeSet::GetMetaElementalBloodDamageAttribute();
	BloodDamageDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	RelevantAttributesToCapture.Add(BloodShieldDef);
	RelevantAttributesToCapture.Add(BloodDamageDef);
}

float UBloodShieldDamageMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Shield
	float BloodShield = 0;
	GetCapturedAttributeMagnitude(BloodShieldDef, Spec, EvaluationParameters, BloodShield);

	// Damage
	float BloodDamage = 0;
	GetCapturedAttributeMagnitude(BloodShieldDef, Spec, EvaluationParameters, BloodDamage);

	if (BloodShield > 0)
	{
		// Add spec magnitude to damage
		BloodDamage += Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Magnitude")),
		true, 0);
		return BloodDamage;
	}
	else
	{
		return 0;
	}
}
