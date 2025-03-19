// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BulletBase.h"


// Sets default values
ABulletBase::ABulletBase():
	AmmoConsumedOnShot(1)
{
	
}

void ABulletBase::ApplyEffectToAbilitySystemComponent
	(UAbilitySystemComponent* AbilitySystemComponent,
	TSubclassOf<UGameplayEffect> GameplayEffect,
	float Magnitude)
{
	if (!GameplayEffect)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid instigator or effect class."));
		return;
	}

	// Make effect context
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	
	// Create an Outgoing Effect Spec
	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect,
		1.f,
		EffectContext);
	EffectSpecHandle.Data.Get()->SetSetByCallerMagnitude
		(FGameplayTag::RequestGameplayTag(FName("Data.Magnitude")),
		Magnitude);
	
	if (!EffectSpecHandle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create GameplayEffectSpec."));
		return;
	}

	// Apply gameplay effect
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}


