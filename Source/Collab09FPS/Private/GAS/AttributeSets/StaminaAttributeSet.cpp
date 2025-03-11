// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AttributeSets/StaminaAttributeSet.h"

UStaminaAttributeSet::UStaminaAttributeSet()
{
	
}

void UStaminaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	//Clamp current stamina value
	if (Attribute == GetCurrentStaminaAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0, GetMaxStamina());
	}
	
	Super::PreAttributeChange(Attribute, NewValue);
}

void UStaminaAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
