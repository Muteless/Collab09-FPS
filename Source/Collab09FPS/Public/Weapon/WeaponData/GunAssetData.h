// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Components/SkeletalMeshComponent.h"
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
		BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	TArray<TSubclassOf<ABulletBase>> Projectiles;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	UAnimMontage* GunReloadAnimation;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float Damage;

	UPROPERTY()
	float AmmoPerShot;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float RateOfFire;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float Range;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	int MagazineSize;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float ReloadTime;
	
protected:
private:
	GENERATED_BODY()
};
