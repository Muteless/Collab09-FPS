// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/EffectExecutions/MagnitudeModifierCalculations/CurseShieldDamageMMC.h"
#include "GAS/AttributeSets/HealthAttributeSet.h"

UCurseShieldDamageMMC::UCurseShieldDamageMMC()
{
	// Shield
	CurseShieldDef.AttributeToCapture = UHealthAttributeSet::GetCurrentCurseShieldAttribute();
	CurseShieldDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	// Damage
	CurseDamageDef.AttributeToCapture = UHealthAttributeSet::GetMetaElementalCurseDamageAttribute();
	CurseDamageDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	RelevantAttributesToCapture.Add(CurseShieldDef);
	RelevantAttributesToCapture.Add(CurseDamageDef);
}

float UCurseShieldDamageMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Shield
	float CurseShield = 0;
	GetCapturedAttributeMagnitude(CurseShieldDef, Spec, EvaluationParameters, CurseShield);

	// Damage
	float CurseDamage = 0;
	GetCapturedAttributeMagnitude(CurseDamageDef, Spec, EvaluationParameters, CurseDamage);

	if (CurseShield > 0)
	{
		// Add spec magnitude to damage
		CurseDamage += Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Magnitude")),
		true, 0);
		return CurseDamage;
	}
	else
	{
		return 0;
	}
}
