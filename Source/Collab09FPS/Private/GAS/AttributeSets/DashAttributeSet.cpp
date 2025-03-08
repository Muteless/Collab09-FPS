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

void UDashAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDashAttributeSet,
		GroundDashSpeed,
		COND_None,
		REPNOTIFY_Always); // Register Ground DashSpeed for replication

	DOREPLIFETIME_CONDITION_NOTIFY(UDashAttributeSet,
		AirDashSpeed,
		COND_None,
		REPNOTIFY_Always); // Register Air DashSpeed for replication
}

void UDashAttributeSet::OnRep_GroundDashSpeed()
{
	// Ground dash speed replicated
}

void UDashAttributeSet::OnRep_AirDashSpeed()
{
	// Air dash speed replicated
}
