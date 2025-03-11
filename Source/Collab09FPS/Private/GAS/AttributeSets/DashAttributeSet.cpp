// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/DashAttributeSet.h"

#include "Net/UnrealNetwork.h"

UDashAttributeSet::UDashAttributeSet()
{
	
}

void UDashAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}