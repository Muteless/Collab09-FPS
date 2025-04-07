// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/EffectExecutions/ShieldDamageExecutionCalculation.h"
#include "GAS/AttributeSets/HealthAttributeSet.h"

UShieldDamageExecutionCalculation::UShieldDamageExecutionCalculation() :
	// Damage
	FireDamageDef(
		UHealthAttributeSet::GetMetaElementalFireDamageAttribute(),
		EGameplayEffectAttributeCaptureSource::Target,
		true),
	CurseDamageDef(
		UHealthAttributeSet::GetMetaElementalCurseDamageAttribute(),
		EGameplayEffectAttributeCaptureSource::Target,
		true),
	BloodDamageDef(
		UHealthAttributeSet::GetMetaElementalBloodDamageAttribute(),
		EGameplayEffectAttributeCaptureSource::Target,
		true),

	// Shields
	FireShieldDef
	(UHealthAttributeSet::GetCurrentFireShieldAttribute(),
		EGameplayEffectAttributeCaptureSource::Target,
		true),
	CurseShieldDef
	(UHealthAttributeSet::GetCurrentCurseShieldAttribute(),
		EGameplayEffectAttributeCaptureSource::Target,
		true),
	BloodShieldDef
	(UHealthAttributeSet::GetCurrentBloodShieldAttribute(),
		EGameplayEffectAttributeCaptureSource::Target,
		true)
{
	RelevantAttributesToCapture.Add(FireDamageDef);
	RelevantAttributesToCapture.Add(CurseDamageDef);
	RelevantAttributesToCapture.Add(BloodDamageDef);
	RelevantAttributesToCapture.Add(FireShieldDef);
	RelevantAttributesToCapture.Add(CurseShieldDef);
	RelevantAttributesToCapture.Add(BloodShieldDef);
}

void UShieldDamageExecutionCalculation::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float IncomingFireDamage = 0.0f;
	float IncomingCurseDamage = 0.0f;
	float IncomingBloodDamage = 0.0f;

	float FireShield = 0.0f;
	float CurseShield = 0.0f;
	float BloodShield = 0.0f;

	// Damage
	if (!ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		FireDamageDef,
		FAggregatorEvaluateParameters(),
		IncomingFireDamage))
	{
		IncomingFireDamage = 0.0f;
	}

	if (!ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		CurseDamageDef,
		FAggregatorEvaluateParameters(),
		IncomingCurseDamage))
	{
		IncomingCurseDamage = 0.0f;
	}

	if (!ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		BloodDamageDef,
		FAggregatorEvaluateParameters(),
		IncomingBloodDamage))
	{
		IncomingBloodDamage = 0.0f;
	}

	// Shields
	if (!ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		FireShieldDef,
		FAggregatorEvaluateParameters(),
		FireShield))
	{
		FireShield = 0.0f;
	}

	if (!ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		CurseShieldDef,
		FAggregatorEvaluateParameters(),
		CurseShield))
	{
		CurseShield = 0.0f;
	}

	if (!ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		BloodShieldDef,
		FAggregatorEvaluateParameters(),
		BloodShield))
	{
		BloodShield = 0.0f;
	}

	if (FireShield > 0)
	{
		float NewShield = FMath::Clamp((FireShield - IncomingFireDamage), 0.f, FireShield);
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData
			(UHealthAttributeSet::GetCurrentFireShieldAttribute(), EGameplayModOp::Override, NewShield));
	}

	if (CurseShield > 0)
	{
		float NewShield = FMath::Clamp((CurseShield - IncomingCurseDamage), 0.f, CurseShield);
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData
			(UHealthAttributeSet::GetCurrentCurseShieldAttribute(), EGameplayModOp::Override, NewShield));
	}

	if (BloodShield > 0)
	{
		float NewShield = FMath::Clamp((BloodShield - IncomingBloodDamage), 0.f, BloodShield);
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData
			(UHealthAttributeSet::GetCurrentBloodShieldAttribute(), EGameplayModOp::Override, NewShield));
	}
}
