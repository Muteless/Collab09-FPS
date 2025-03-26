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
	
#pragma region GunData
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Gun")
	UGunAssetData* GunAssetData;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Gun")
	float CurrentAmmo;

#pragma endregion GunData

#pragma region MeleeData
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Melee")
	UMeleeAssetData* MeleeAssetData;
	
#pragma endregion MeleeData

#pragma region World

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "World")
	EWorldState WorldState;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "World")
	TArray<int> InactiveSpawnersIds;
	
#pragma endregion World

private:
	GENERATED_BODY()
};
