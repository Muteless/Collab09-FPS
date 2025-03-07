// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/AirActionAttributeSet.h"

#include "Net/UnrealNetwork.h"

UAirActionAttributeSet::UAirActionAttributeSet()
{
	MaxAirActions.SetBaseValue(2.0f);
	CurrentAirActions.SetBaseValue(MaxAirActions.GetBaseValue());
}


void UAirActionAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAirActionAttributeSet,
		CurrentAirActions,
		COND_None,
		REPNOTIFY_Always); // Register Current Health for replication

	DOREPLIFETIME_CONDITION_NOTIFY(UAirActionAttributeSet,
		MaxAirActions,
		COND_None,
		REPNOTIFY_Always); // Register Max Health for replication
}

void UAirActionAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	// Current air actions
	if (Attribute == GetCurrentAirActionsAttribute())
	{
		SetCurrentAirActions(FMath::Clamp<float>(NewValue,
			0,
			GetMaxAirActions()));
	}
}

void UAirActionAttributeSet::OnRep_MaxAirActions()
{
	// Max air actions has been replicated
}

void UAirActionAttributeSet::OnRep_CurrentAirActions()
{
	// Current air actions has been replicated
}