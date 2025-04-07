// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AttributeSets/HealthAttributeSet.h"

UHealthAttributeSet::UHealthAttributeSet()
{
	// Health
	MaxHealth.SetBaseValue(100);
	CurrentHealth.SetBaseValue(100);

	// Shield
	MaxFireShield.SetBaseValue(0.0f);
	CurrentFireShield.SetBaseValue(0.0f);
	
	MaxCurseShield.SetBaseValue(0.0f);
	CurrentCurseShield.SetBaseValue(0.0f);
	
	MaxBloodShield.SetBaseValue(0.0f);
	CurrentBloodShield.SetBaseValue(0.0f);

	// Damage
	MetaElementalFireDamage.SetBaseValue(0.0f);
	MetaElementalCurseDamage.SetBaseValue(0.0f);
	MetaElementalBloodDamage.SetBaseValue(0.0f);
	MetaDamage.SetBaseValue(0);

	// Healing
	MetaHeal.SetBaseValue(0);
}

void UHealthAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	// Health
	if (Attribute == GetCurrentHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0, GetMaxHealth());
		return;
	}
	
	// Fire
	if (Attribute == GetCurrentFireShieldAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetMaxFireShield());
		return;
	}

	// Curse
	if (Attribute == GetCurrentCurseShieldAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetMaxCurseShield());
		return;
	}

	// Blood
	if (Attribute == GetCurrentBloodShieldAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetMaxBloodShield());
		return;
	}
	
	Super::PreAttributeBaseChange(Attribute, NewValue);
}