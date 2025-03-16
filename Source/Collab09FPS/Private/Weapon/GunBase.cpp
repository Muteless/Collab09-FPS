// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GunBase.h"

#include "Projectile/ProjectileBase.h"


// Sets default values
AGunBase::AGunBase():
	ProjectileSpawnLocation(nullptr),
	WeaponMesh(nullptr),
	RateOfFire(1),
	CurrentProjectileIndex(0),
	MagazineSize(0),
	CurrentAmmo(0),
	bIsReloading(false)
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	ProjectileSpawnLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnLocation"));
	ProjectileSpawnLocation->SetupAttachment(WeaponMesh);
}

void AGunBase::Fire(bool bIncrementCurrentIndex)
{
	if (CanFire() && ProjectileClasses[CurrentProjectileIndex] != nullptr)
	{
		// Get spawn location and rotation from the ProjectileSpawnLocation (Arrow Component)
		const FVector SpawnLocation = ProjectileSpawnLocation ? ProjectileSpawnLocation->GetComponentLocation() : GetActorLocation();
		const FRotator SpawnRotation = ProjectileSpawnLocation ? ProjectileSpawnLocation->GetComponentRotation() : GetActorRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Spawn the projectile
		ABulletBase* SpawnedProjectile = GetWorld()->SpawnActor<ABulletBase>(
			ProjectileClasses[CurrentProjectileIndex], // Projectile class (e.g., AProjectile)
			SpawnLocation,                             // Location
			SpawnRotation,                             // Rotation
			SpawnParams                                // Parameters
		);

		if (SpawnedProjectile)
		{
			ConsumeAmmo(SpawnedProjectile->AmmoConsumedOnShot);
		}

		// start ROF timer
		GetWorld()->GetTimerManager().SetTimer(
			RateOfFireTimerHandle,
			this,
			&AGunBase::FinishReload,
			RateOfFire,
			false
			);
	}
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
	
	// If we are NOT reloading, and we have ammo and ROF timer is NOT active return true
	if (!IsReloading() && HasAmmo() && !GetWorld()->GetTimerManager().IsTimerActive(RateOfFireTimerHandle))
	{
		return true;
	}
	
	return false;
}

bool AGunBase::HasAmmo() const
{
	return CurrentAmmo > 0;
}

void AGunBase::ConsumeAmmo(const int AmmoAmountToConsume)
{
	CurrentAmmo -= AmmoAmountToConsume;
}

void AGunBase::StartReload()
{
	if (CanReload())
	{
		bIsReloading = true;
	}
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
	return CurrentAmmo < MagazineSize;
}

void AGunBase::Initialize()
{
	
}

