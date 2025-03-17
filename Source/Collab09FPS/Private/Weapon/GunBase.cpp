// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GunBase.h"

#include "Projectile/ProjectileBase.h"


// Sets default values
AGunBase::AGunBase()
{
	ProjectileSpawnLocation = nullptr;
	WeaponMesh = nullptr;
	CurrentProjectileIndex = 0;
	CurrentAmmo = 0;
	MagazineSize = 0;
	RateOfFire = 1;
	bIsReloading = false;
	
	if (GunAssetData)
	{
		Name = GunAssetData->Name;
		Projectile = GunAssetData->Projectile;
		Damage = GunAssetData->Damage;
		RateOfFire = GunAssetData->RateOfFire;
		Range = GunAssetData->Range;
		MagazineSize = GunAssetData->MagazineSize;
		ReloadTime = GunAssetData->ReloadTime;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GunAssetData not set for: %s"), *GetName());
	}
	
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	// Gun mesh
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	WeaponMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	
	// Projectile spawn location
	ProjectileSpawnLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnLocation"));
	ProjectileSpawnLocation->SetupAttachment(WeaponMesh);
}

void AGunBase::Initialize()
{
	SetMeshVisibility(false);
}

USkeletalMesh* AGunBase::GetWeaponMesh()
{
	return WeaponMesh->GetSkeletalMeshAsset();
}

void AGunBase::Fire(bool bIncrementCurrentIndex)
{
	if (CanFire() && Projectiles[CurrentProjectileIndex] != nullptr)
	{
		// Get spawn location and rotation from the ProjectileSpawnLocation (Arrow Component)
		const FVector SpawnLocation = ProjectileSpawnLocation ? ProjectileSpawnLocation->GetComponentLocation() : GetActorLocation();
		const FRotator SpawnRotation = ProjectileSpawnLocation ? ProjectileSpawnLocation->GetComponentRotation() : GetActorRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Spawn the projectile
		ABulletBase* SpawnedProjectile = GetWorld()->SpawnActor<ABulletBase>(
			Projectiles[CurrentProjectileIndex],
			SpawnLocation,
			SpawnRotation,
			SpawnParams
			);

		if (SpawnedProjectile)
		{
			ConsumeAmmo(SpawnedProjectile->AmmoConsumedOnShot);
		}

		// start ROF timer
		GetWorld()->GetTimerManager().SetTimer(
			RateOfFireTimerHandle,
			this,
			&AGunBase::RofFinished,
			RateOfFire,
			false
			);
	}
}

void AGunBase::RofFinished()
{
	
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
		
		// start reload timer
		GetWorld()->GetTimerManager().SetTimer(
			ReloadTimerHandle,
			this,
			&AGunBase::FinishReload,
			RateOfFire,
			false
			);
	}
}

bool AGunBase::IsReloading() const
{
	return bIsReloading;
}

void AGunBase::FinishReload()
{
	CurrentAmmo = MagazineSize;
	WeaponReloaded.Broadcast();
}

bool AGunBase::CanReload() const
{
	return CurrentAmmo < MagazineSize && !GetWorld()->GetTimerManager().IsTimerActive(ReloadTimerHandle);
}

void AGunBase::SetMeshVisibility(bool bVisible)
{
	if (bVisible)
	{
		WeaponMesh->SetVisibility(true);
	}
	else
	{
		WeaponMesh->SetVisibility(false);
	}
}
