// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"



#include "MeleeAbilityBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class COLLAB09FPS_API UMeleeAbilityBase : public UGameplayAbility
{
public:
	UMeleeAbilityBase();
	
	// This function will be triggered when the ability is activated
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
								 const FGameplayAbilityActorInfo* ActorInfo, 
								 const FGameplayAbilityActivationInfo ActivationInfo, 
								 const FGameplayEventData* TriggerEventData) override;

protected:
	// Melee range box dimensions
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Melee | Range | ")
	FVector MeleeRangeBox;

	// Melee damage
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Melee | ")
	float MeleeDamage;

	// Melee effect class
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Melee | ")
	TSubclassOf<UGameplayEffect> HitEffect;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Melee | ")
	TEnumAsByte<ECollisionChannel> MeleeCollisionChannel;
private:
	GENERATED_BODY()
};
