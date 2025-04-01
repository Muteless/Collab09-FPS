// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletBase.h"

#include "AbilitySystemComponent.h"

#include "HitscanBase.generated.h"

UCLASS()
class COLLAB09FPS_API AHitscanBase : public ABulletBase
{
public:
	// Sets default values for this actor's properties
	AHitscanBase();
	virtual void Initialize() override;

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void ApplyGameplayEffectsToHit(FHitResult Hit);
	void ApplyGameplayEffectsToHit_Implementation(FHitResult Hit);

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	float Range = 1000;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	bool Pierce = false;
	
private:
	GENERATED_BODY()
};
