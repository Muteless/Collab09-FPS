// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GunBase.h"


// Sets default values
AGunBase::AGunBase():
	ProjectileSpawnLocation(nullptr),
	WeaponMesh(nullptr),
	CurrentProjectileIndex(0),
	MagazineSize(0),
	CurrentAmmo(0),
	bIsReloading(false)
{
	
}

void AGunBase::Fire(bool bIncrementCurrentIndex)
{
	if (CanFire() && ProjectileClasses[CurrentProjectileIndex] != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
	}

	const FVector SpawnLocation = GetActorLocation();
}

bool AGunBase::CanFire() const
{
	// broadcast we have no ammo
	if (!HasAmmo())
	{
		WeaponFailedToFireNoAmmo.Broadcast();
	}

	// broadcast we are reloading
	if (IsReloading())
	{
		WeaponFailedToFireReloading.Broadcast();
	}
	
	// If we are NOT reloading and we have ammo return true
	if (!IsReloading() && HasAmmo())
	{
		return true;
	}
	
	return false;
}

bool AGunBase::HasAmmo() const
{
	return CurrentAmmo > 0;
}

void AGunBase::StartReload()
{
	
}

bool AGunBase::IsReloading() const
{
	return bIsReloading;
}

void AGunBase::FinishReload()
{
	
}

bool AGunBase::CanReload() const
{
	return true;
}

void AGunBase::Initialize()
{
	
}

