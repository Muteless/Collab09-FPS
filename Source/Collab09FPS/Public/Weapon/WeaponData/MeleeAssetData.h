// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Animation/AnimMontage.h"
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
	FName Name;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	TArray<TSubclassOf<UGameplayEffect>> OnHitGameplayEffects;

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
