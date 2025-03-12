// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/EffectExecutions/MagnitudeModifierCalculations/DamageMMC.h"
#include "GAS/AttributeSets/HealthAttributeSet.h"


UDamageMMC::UDamageMMC()
{
	DamageDef.AttributeToCapture = UHealthAttributeSet::GetMetaDamageAttribute();
	DamageDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

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

	float Damage = 0;
	GetCapturedAttributeMagnitude(DamageDef, Spec, EvaluationParameters, Damage);

	// Add spec magnitude to damage
	Damage += Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Magnitude")),
		true, 0);
	
	return Damage;
}
