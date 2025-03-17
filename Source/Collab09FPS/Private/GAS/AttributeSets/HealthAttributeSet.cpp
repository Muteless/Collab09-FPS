// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AttributeSets/HealthAttributeSet.h"

UHealthAttributeSet::UHealthAttributeSet()
{
	
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
