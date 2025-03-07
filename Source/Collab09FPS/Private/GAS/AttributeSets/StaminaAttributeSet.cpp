// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AttributeSets/StaminaAttributeSet.h"
#include "Net/UnrealNetwork.h"



void UStaminaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	//Clamp current stamina value
	if (Attribute == GetCurrentStaminaAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0, GetMaxStamina());
	}
}

void UStaminaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UStaminaAttributeSet,
		CurrentStamina,
		COND_None,
		REPNOTIFY_Always); // Register Current Stamina for replication
	
	DOREPLIFETIME_CONDITION_NOTIFY(UStaminaAttributeSet,
		MaxStamina,
		COND_None,
		REPNOTIFY_Always); // Register Max Stamina for replication
}


void UStaminaAttributeSet::OnRep_MaxStamina()
{
	// Max stamina replicated
}

void UStaminaAttributeSet::OnRep_CurrentStamina()
{
	// Current stamina replicated
}
