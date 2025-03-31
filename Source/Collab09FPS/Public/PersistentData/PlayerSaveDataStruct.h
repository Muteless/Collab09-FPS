// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "Weapon/WeaponData/GunAssetData.h"
#include "Weapon/WeaponData/MeleeAssetData.h"

#include "PlayerSaveDataStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	bool bGunMode;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	UGunAssetData* GunAssetData;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	UMeleeAssetData* MeleeAssetData;
	
	FPlayerData()
		: bGunMode(false)
		, GunAssetData(nullptr)
		, MeleeAssetData(nullptr)
	{}
};

UCLASS()
class COLLAB09FPS_API UPlayerSaveDataStruct : public UObject
{
public:
private:
	GENERATED_BODY()
};
