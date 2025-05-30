﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NiagaraSystem.h"
#include "GameplayEffect.h"
#include "Engine/Texture2D.h"

#include "BulletBase.generated.h"

UCLASS(Abstract)
class COLLAB09FPS_API ABulletBase : public AActor
{

public:
	// Sets default values for this actor's properties
	ABulletBase();

	UFUNCTION(BlueprintCallable)
	virtual void Initialize();

	UFUNCTION(BlueprintCallable, meta = (HidePin = "Target"))
	void ApplyEffectToAbilitySystemComponent
		(UAbilitySystemComponent* AbilitySystemComponent,
		TSubclassOf<UGameplayEffect> GameplayEffect,
		float Magnitude, FHitResult HitResult);
	
	// Amount of ammo consumed on shot
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	float AmmoConsumedOnShot;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	TMap<TSubclassOf<class UGameplayEffect>, float> OnHitGameplayEffect;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	UNiagaraSystem* OnHitSystem;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	FColor BulletColor = FColor::White;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	UTexture2D* BulletIcon;
	
protected:
private:
	GENERATED_BODY()
};
