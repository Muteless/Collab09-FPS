// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/HitscanBase.h"


// Sets default values
AHitscanBase::AHitscanBase()
{
	
}

void AHitscanBase::Initialize()
{
	Super::Initialize();

	FVector Start = GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * Range);

	
	FCollisionQueryParams TraceParams;
	
	if (Pierce)
	{
		// multi line trace
		TArray<FHitResult> Hits;
		
		if (GetWorld()->LineTraceMultiByChannel(
			Hits,
			Start,
			End,
			ECC_GameTraceChannel1,
			TraceParams))
		{
			// apply effects to hit
			for (FHitResult Hit : Hits)
			{
				ApplyGameplayEffectsToHit(Hit);
			}
		}
	}
	else
	{
		// hit line trace
		FHitResult Hit;

		if (GetWorld()->LineTraceSingleByChannel(
			Hit,
			Start,
			End,
			ECC_GameTraceChannel1,
			TraceParams))
		{
			// apply effects to hit
			ApplyGameplayEffectsToHit(Hit);
		}
	}
	
	Destroy();
}

void AHitscanBase::ApplyGameplayEffectsToHit_Implementation(FHitResult Hit)
{
	
}
