// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Weapon/WeaponData/GunAssetData.h"
#include "Weapon/WeaponData/MeleeAssetData.h"
#include "Collab09FPS/Collab09FPS.h"

#include "PlayerSaveData.generated.h"

/**
 * 
 */

UCLASS()
class COLLAB09FPS_API UPlayerSaveData : public UDataAsset
{
public:
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Weapon")
	bool bGunMode;
	
#pragma region GunData
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Weapon|Gun")
	UGunAssetData* GunAssetData;

#pragma endregion GunData

#pragma region MeleeData
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Weapon|Melee")
	UMeleeAssetData* MeleeAssetData;
	
#pragma endregion MeleeData

private:
	GENERATED_BODY()
};
