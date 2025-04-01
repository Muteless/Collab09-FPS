// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BulletBase.h"
#include "AbilitySystemComponent.h"


// Sets default values
ABulletBase::ABulletBase():
AmmoConsumedOnShot(1),
OnHitSystem(nullptr)
{
	
}

void ABulletBase::Initialize()
{
	
}

void ABulletBase::ApplyEffectToAbilitySystemComponent
	(UAbilitySystemComponent* AbilitySystemComponent,
	TSubclassOf<UGameplayEffect> GameplayEffect,
	float Magnitude,
	FHitResult HitResult)
{
	if (AbilitySystemComponent)
	{
		if (!GameplayEffect)
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid instigator or effect class."));
			return;
		}

		// Make effect context
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		EffectContext.AddHitResult(HitResult);
	
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
		
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}


