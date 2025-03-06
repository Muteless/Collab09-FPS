// Fill out your copyright notice in the Description page of Project Settings.


#include "Collab09FPS/Public/Weapon/WeaponBase.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	// Default variables
	RateOfFire = BaseRateOfFire;
	ReloadSpeed = BaseReloadSpeed;
	CurrentAmmoAmount = MaxAmmoAmount;
	CurrentProjectileIndex = 0;
	CurrentMeleeAbilityIndex = 0;

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
	return !RateOfFireTimerHandle.IsValid() && CurrentAmmoAmount > 0;
}

// Fire weapon
void AWeaponBase::Fire(const int AmmoConsumption, bool bIncrementCurrentIndex)
{
	// If weapon can Fire & projectile class is valid
	if (CanFire() && ProjectileClasses[CurrentProjectileIndex] != nullptr)
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
		GetWorld()->SpawnActor<AProjectileBase>(ProjectileClasses[CurrentProjectileIndex], SpawnLocation, SpawnRotation, SpawnParams);

		// Start rate of fire timer
		GetWorld()->GetTimerManager().SetTimer(RateOfFireTimerHandle, RateOfFire, false);

		// Increment current index
		if (bIncrementCurrentIndex)
		{
			CurrentProjectileIndex++;
			if (CurrentProjectileIndex >= ProjectileClasses.Num())
			{
				CurrentProjectileIndex = 0;
			}
		}
		
		// Consume ammo
		ConsumeAmmo(AmmoConsumption);
	}	else 
	{
		// weapon has failed to fire
		WeaponFailedToFire.Broadcast();
	}
}

// Can reload
bool AWeaponBase::CanReload() const
{
	return CurrentAmmoAmount < MaxAmmoAmount;
}

// Reload weapon
void AWeaponBase::Reload()
{
	if (CanReload())
	{
		// Bind timer handle when finished
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle,
			this,
			&AWeaponBase::ReloadComplete,
			ReloadSpeed,
			false);

		// Broadcast that we have started to reload
		WeaponStartedReload.Broadcast();
	}
	else
	{
		WeaponFailedToReload.Broadcast();
	}
}

void AWeaponBase::ReloadComplete()
{
	// Reset current ammo to max ammo
	CurrentAmmoAmount = MaxAmmoAmount;
	WeaponReloaded.Broadcast();
}

// Consumes ammo
void AWeaponBase::ConsumeAmmo(const int AmmoConsumption)
{
	CurrentAmmoAmount -= AmmoConsumption;
	WeaponAmmoConsumed.Broadcast();
}

// Melee attack
TSubclassOf<UMeleeAbilityBase> AWeaponBase::Melee(const bool bIncrementCurrentIndex)
{
	if (CanMelee())
	{
		// Increment current index
		if (bIncrementCurrentIndex)
		{
			CurrentMeleeAbilityIndex++;
			if (CurrentMeleeAbilityIndex >= MeleeAbilityClasses.Num())
			{
				CurrentMeleeAbilityIndex = 0;
			}
		}
		WeaponMelee.Broadcast();
		return MeleeAbilityClasses[CurrentMeleeAbilityIndex];
	}
	else
	{
		// Weapon has failed to melee
		WeaponFailedToMelee.Broadcast();
	}
	
	return nullptr;
}

bool AWeaponBase::CanMelee() const
{
	// Melee classes can't be empty
	return !MeleeAbilityClasses.IsEmpty();
}