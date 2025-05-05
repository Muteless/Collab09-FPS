// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Animation/AnimMontage.h"
#include "Animation/AnimSequence.h"
#include "GameplayEffect.h"

#include "MeleeAssetData.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UMeleeAssetData : public UDataAsset
{
public:

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	TMap<TSubclassOf<UGameplayEffect>, float> OnHitGameplayEffects;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	TArray<UAnimMontage*> MeleeAnimations;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	float Damage;
	
protected:
private:
	GENERATED_BODY()
};
