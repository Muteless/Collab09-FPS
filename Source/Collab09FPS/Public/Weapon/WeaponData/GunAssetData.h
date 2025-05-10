// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequence.h"
#include "Projectile/BulletBase.h"

#include "GunAssetData.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UGunAssetData : public UDataAsset
{
public:

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	TArray<TSubclassOf<ABulletBase>> Projectiles;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	UAnimMontage* GunReloadAnimation;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	UNiagaraSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	float RateOfFire;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	float Range;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	int MagazineSize;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	float ReloadTime;
	
protected:
private:
	GENERATED_BODY()
};
