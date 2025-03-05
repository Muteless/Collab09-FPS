// Fill out your copyright notice in the Description page of Project Settings.

#include "Net/UnrealNetwork.h"
#include "GAS/AttributeSets/HealthAttributeSet.h"

void UHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	//Clamp current health value
	if (Attribute == GetCurrentHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0, GetMaxHealth());
	}
}

// Unreal Replication System
void UHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet,
		CurrentHealth,
		COND_None,
		REPNOTIFY_Always); // Register Current Health for replication
	
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet,
		MaxHealth,
		COND_None,
		REPNOTIFY_Always); // Register Max Health for replication
}

// OnRep functions (out of scope for this project but hey! it's a habit of mine)
void UHealthAttributeSet::OnRep_MaxHealth()
{
	// Max health has been replicated
}

void UHealthAttributeSet::OnRep_CurrentHealth()
{
	// Current health has been replicated
}
