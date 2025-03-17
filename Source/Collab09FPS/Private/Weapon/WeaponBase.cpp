// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"


// Sets default values
AWeaponBase::AWeaponBase():
	bGunMode(false)
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AWeaponBase::Initialize()
{
	// Setup weapon mode
	if (bGunMode)
	{
		SetupGunVariables();
		SetWeaponModeToGun();
	}
	else
	{
		SetupMeleeVariables();
		SetWeaponModeToMelee();
	}
}

void AWeaponBase::SetupMeleeVariables()
{
	if (MeleeAssetData)
	{
		MeleeAnimations = MeleeAssetData->MeleeAnimations;
		MeleeDamage = MeleeAssetData->Damage;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MeleeAssetData is not set!"));
	}
}

void AWeaponBase::SetWeaponModeToMelee()
{
	
}

void AWeaponBase::WeaponFire_Implementation()
{
	
}

void AWeaponBase::WeaponReload_Implementation()
{
	
}

void AWeaponBase::WeaponReloadInterrupt_Implementation()
{
	
}

void AWeaponBase::WeaponSwitch_Implementation()
{
	bGunMode = !bGunMode;

	if (bGunMode)
	{
		// SetWeaponModeToGun();
	}
	else
	{
		// SetWeaponModeToMelee();
	}
}

bool AWeaponBase::GetWeaponMode_Implementation()
{
	return bGunMode;
}

void AWeaponBase::SetupGunVariables()
{
}

void AWeaponBase::SetWeaponModeToGun()
{
	
}
