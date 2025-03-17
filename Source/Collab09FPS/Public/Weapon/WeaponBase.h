// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interfaces/WeaponInput.h"

#include "Components/SkeletalMeshComponent.h"
#include "WeaponData/MeleeAssetData.h"
#include "WeaponData/GunAssetData.h"

#include "WeaponBase.generated.h"

UCLASS(Abstract)
class COLLAB09FPS_API AWeaponBase : public AActor,
public IWeaponInput
{
public:
	// Sets default values for this actor's properties
	AWeaponBase();

	UFUNCTION(BlueprintCallable)
	void Initialize();

	virtual void WeaponFire_Implementation() override;
	virtual void WeaponReload_Implementation() override;
	virtual void WeaponReloadInterrupt_Implementation() override;
	virtual void WeaponSwitch_Implementation() override;
	virtual bool GetWeaponMode_Implementation() override;

	void SetupGunVariables();
	void SetWeaponModeToGun();

	void SetupMeleeVariables();
	void SetWeaponModeToMelee();
	
protected:
	UPROPERTY()
	FName Name;

	UPROPERTY()
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	UGunAssetData* GunAssetData;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	UMeleeAssetData* MeleeAssetData;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	bool bGunMode;

#pragma region Internal Attributes
#pragma region Melee
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	TArray<UAnimMontage*> MeleeAnimations;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float MeleeDamage;
	
#pragma endregion Melee
	
#pragma region Gun
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	UAnimMontage* GunReloadAnimation;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float GunDamage;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float RateOfFire;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float Range;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	int32 MagazineSize;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float ReloadTime;
	
#pragma endregion Gun
	
#pragma endregion Internal Attributes
	
private:
	GENERATED_BODY()
};
