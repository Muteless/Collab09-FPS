// Fill out your copyright notice in the Description page of Project Settings.


#include "Collab09FPS/Public/Weapon/WeaponBase.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	// Default variables
	ProjectileClass = nullptr;
	RateOfFire = BaseRateOfFire;
	ReloadSpeed = BaseReloadSpeed;
	CurrentAmmoAmount = MaxAmmoAmount;

	// Create weapon SkeletalMeshComponent
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	
	// Create ProjectileSpawnLocation UArrowComponent
	ProjectileSpawnLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Projectile Spawn Location"));
	ProjectileSpawnLocation->ArrowSize = 0.5;
	ProjectileSpawnLocation->ArrowColor = FColor::FromHex("FFFF00FF");
	
}

// Returns if fire can be executed
bool AWeaponBase::CanFire() const
{
	return CurrentAmmoAmount > 0;
}

void AWeaponBase::Fire(const int AmmoConsumption)
{
	// If projectile class is valid & Can Fire
	if (CanFire() && ProjectileClass != nullptr)
	{
		// Setup spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Get spawn location from ProjectileSpawnLocation
		const FVector SpawnLocation = ProjectileSpawnLocation->GetComponentLocation();

		//Get spawn rotation from ProjectileSpawnLocation
		const FRotator SpawnRotation = ProjectileSpawnLocation->GetComponentRotation();

		// Spawn projectile at ProjectileSpawn
		GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
		
		// Consume ammo
		ConsumeAmmo(AmmoConsumption);
	}
}

// Reload weapon
void AWeaponBase::Reload()
{
	// Create timer handle
	FTimerHandle TimerHandle;

	// Bind timer handle when finished
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,
		this,
		&AWeaponBase::ReloadComplete,
		ReloadSpeed,
		false);

	// Broadcast that we have started to reload
	WeaponStartedReload.Broadcast();
}

void AWeaponBase::ReloadComplete()
{
	// Reset current ammo to max ammo
	CurrentAmmoAmount = MaxAmmoAmount;
	WeaponReloaded.Broadcast();
}

// Ammo is not max ammo
bool AWeaponBase::CanReload() const
{
	return CurrentAmmoAmount < MaxAmmoAmount;
}

// Consumes ammo
void AWeaponBase::ConsumeAmmo(const int AmmoConsumption)
{
	CurrentAmmoAmount -= AmmoConsumption;
}

// Melee attack
void AWeaponBase::Melee()
{
	if (CanMelee())
	{
		StartedMelee.Broadcast();
	}
}

bool AWeaponBase::CanMelee()
{
	// TODO: Implement can melee with GAS?
	return true;
}
