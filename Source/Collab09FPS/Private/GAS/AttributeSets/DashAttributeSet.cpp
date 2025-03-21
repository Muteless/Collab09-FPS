// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/DashAttributeSet.h"

#include "Net/UnrealNetwork.h"

UDashAttributeSet::UDashAttributeSet()
{
	GroundDashSpeed.SetBaseValue(4000);
	GroundDashCooldown.SetBaseValue(1);
	GroundDashStaminaCost.SetBaseValue(25);
	AirDashSpeed.SetBaseValue(4000);
	AirDashCooldown.SetBaseValue(1);
	AirDashStaminaCost.SetBaseValue(25);
}

void UDashAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}