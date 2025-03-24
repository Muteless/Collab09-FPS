// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AttributeSets/HealthAttributeSet.h"

UHealthAttributeSet::UHealthAttributeSet()
{
	MaxHealth.SetBaseValue(100);
	CurrentHealth.SetBaseValue(100);
	MetaDamage.SetBaseValue(0);
	MetaHeal.SetBaseValue(0);
}

void UHealthAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetCurrentHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0, GetMaxHealth());
	}
	
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UHealthAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue,
	float NewValue) const
{
	
}
