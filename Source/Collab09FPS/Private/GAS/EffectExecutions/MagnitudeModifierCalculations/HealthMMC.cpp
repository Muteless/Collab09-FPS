// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/EffectExecutions/MagnitudeModifierCalculations/HealthMMC.h"
#include "GAS/AttributeSets/HealthAttributeSet.h"

UHealthMMC::UHealthMMC()
{
	HealDef.AttributeToCapture = UHealthAttributeSet::GetMetaHealAttribute();
	HealDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	RelevantAttributesToCapture.Add(HealDef);
}

float UHealthMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	float Heal = 0;
	GetCapturedAttributeMagnitude(HealDef, Spec, EvaluationParameters, Heal);
	
	// Add spec magnitude to heal
	Heal += Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Magnitude")),
		true, 0);
	return Heal;
}