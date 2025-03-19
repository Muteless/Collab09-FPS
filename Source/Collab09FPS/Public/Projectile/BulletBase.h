// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

#include "BulletBase.generated.h"

UCLASS(Abstract)
class COLLAB09FPS_API ABulletBase : public AActor
{

public:
	// Sets default values for this actor's properties
	ABulletBase();

	UFUNCTION(BlueprintCallable, meta = (HidePin = "Target"))
	void ApplyEffectToAbilitySystemComponent
		(UAbilitySystemComponent* AbilitySystemComponent,
		TSubclassOf<UGameplayEffect> GameplayEffect,
		float Magnitude);
	
	// Amount of ammo consumed on shot
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Bullet |")
	float AmmoConsumedOnShot;
	
protected:
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Bullet |")
	TMap<TSubclassOf<class UGameplayEffect>, float> OnHitGameplayEffect;
	
private:
	GENERATED_BODY()
};
