// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/AirActionAttributeSet.h"

#include "Net/UnrealNetwork.h"

UAirActionAttributeSet::UAirActionAttributeSet()
{
	MaxAirActions.SetBaseValue(2.0f);
	CurrentAirActions.SetBaseValue(MaxAirActions.GetBaseValue());
}