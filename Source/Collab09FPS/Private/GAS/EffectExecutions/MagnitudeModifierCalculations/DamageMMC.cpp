// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/EffectExecutions/MagnitudeModifierCalculations/DamageMMC.h"
#include "GAS/AttributeSets/HealthAttributeSet.h"


UDamageMMC::UDamageMMC()
{
	// Shield
	FireShieldDef.AttributeToCapture = UHealthAttributeSet::GetCurrentFireShieldAttribute();
	FireShieldDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	CurseShieldDef.AttributeToCapture = UHealthAttributeSet::GetCurrentCurseShieldAttribute();
	CurseShieldDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	BloodShieldDef.AttributeToCapture = UHealthAttributeSet::GetCurrentBloodShieldAttribute();
	BloodShieldDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	// Damage
	DamageDef.AttributeToCapture = UHealthAttributeSet::GetMetaDamageAttribute();
	DamageDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	
	RelevantAttributesToCapture.Add(FireShieldDef);
	RelevantAttributesToCapture.Add(CurseShieldDef);
	RelevantAttributesToCapture.Add(BloodShieldDef);
	RelevantAttributesToCapture.Add(DamageDef);
}

float UDamageMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
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

	float CurseShield = 0;
	GetCapturedAttributeMagnitude(CurseShieldDef, Spec, EvaluationParameters, CurseShield);

	float BloodShield = 0;
	GetCapturedAttributeMagnitude(BloodShieldDef, Spec, EvaluationParameters, BloodShield);

	// Damage
	float Damage = 0;
	GetCapturedAttributeMagnitude(DamageDef, Spec, EvaluationParameters, Damage);

	if (FireShield > 0 || CurseShield > 0 || BloodShield > 0)
	{
		return 0;
	}
	else
	{
		// Add spec magnitude to damage
		Damage += Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Magnitude")),
		true, 0);
		return Damage;
	}
}
