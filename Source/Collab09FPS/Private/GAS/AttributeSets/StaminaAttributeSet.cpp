// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AttributeSets/StaminaAttributeSet.h"

UStaminaAttributeSet::UStaminaAttributeSet()
{
	MaxStamina.SetBaseValue(100.0f);
	CurrentStamina.SetBaseValue(100.0f);
	StaminaReplenishRate.SetBaseValue(0);
	StaminaReplenishAmount.SetBaseValue(0);
	StaminaReplenishInhibitDuration.SetBaseValue(0);
}

void UStaminaAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	//Clamp current stamina value
	if (Attribute == GetCurrentStaminaAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0, GetMaxStamina());
	}
	
	Super::PreAttributeBaseChange(Attribute, NewValue);
}