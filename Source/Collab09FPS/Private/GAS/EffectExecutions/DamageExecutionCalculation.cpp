// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/EffectExecutions/DamageExecutionCalculation.h"
#include "GAS/AttributeSets/HealthAttributeSet.h"

UDamageExecutionCalculation::UDamageExecutionCalculation() :
	// Health
	HealthDef(
		UHealthAttributeSet::GetCurrentHealthAttribute(),
		EGameplayEffectAttributeCaptureSource::Target,
		true),

	// Damage
	DamageDef(
		UHealthAttributeSet::GetMetaDamageAttribute(),
		EGameplayEffectAttributeCaptureSource::Target,
		true),

	// Shields
	FireShieldDef(
		UHealthAttributeSet::GetCurrentFireShieldAttribute(),
		EGameplayEffectAttributeCaptureSource::Target,
		true),
	CurseShieldDef(
		UHealthAttributeSet::GetCurrentCurseShieldAttribute(),
		EGameplayEffectAttributeCaptureSource::Target,
		true),
	BloodShieldDef(
		UHealthAttributeSet::GetCurrentBloodShieldAttribute(),
		EGameplayEffectAttributeCaptureSource::Target,
		true)
{
	
	RelevantAttributesToCapture.Add(HealthDef);
	RelevantAttributesToCapture.Add(DamageDef);
	RelevantAttributesToCapture.Add(FireShieldDef);
	RelevantAttributesToCapture.Add(CurseShieldDef);
	RelevantAttributesToCapture.Add(BloodShieldDef);

}

void UDamageExecutionCalculation::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float CurrentHealth = 0.0f;
	float IncomingDamage = 0.0f;

	float FireShield = 0.0f;
	float CurseShield = 0.0f;
	float BloodShield = 0.0f;

	// Health
	if (!ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		HealthDef,
		FAggregatorEvaluateParameters(),
		CurrentHealth))
	{
		CurrentHealth = 0.0f;
	}
	
	// Damage
	if (!ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageDef,
		FAggregatorEvaluateParameters(),
		IncomingDamage))
	{
		IncomingDamage = 0.0f;
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

	if (FireShield > 0 || CurseShield > 0 || BloodShield > 0)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData
			(UHealthAttributeSet::GetMetaDamageAttribute(), EGameplayModOp::Override, 0));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), IncomingDamage);
		float NewHealth = FMath::Clamp((CurrentHealth - IncomingDamage), 0.f, CurrentHealth);

		UE_LOG(LogTemp, Warning, TEXT("New Health: %f"), NewHealth);
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData
			(UHealthAttributeSet::GetCurrentHealthAttribute(), EGameplayModOp::Override, NewHealth));
	}
}
