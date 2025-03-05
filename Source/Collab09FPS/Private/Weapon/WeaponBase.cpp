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

	// Setup weapon skeletal mesh
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	
	// Setup projectile spawn location
	ProjectileSpawnLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Projectile Spawn Location"));
	ProjectileSpawnLocation->ArrowSize = 0.5;
	ProjectileSpawnLocation->ArrowColor = FColor::FromHex("FFFF00FF");
	
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponBase::Fire(const int AmmoConsumption)
{
	// If projectile class is valid
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
	}
	// Consume ammo
	ConsumeAmmo(AmmoConsumption);
}

// Melee attack
void AWeaponBase::Melee()
{
	
}

// Start reloading weapon
void AWeaponBase::StartReload()
{
	// Create timer handle
	FTimerHandle TimerHandle;

	// Bind timer handle when finished
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,
		this,
		&AWeaponBase::Reload,
		ReloadSpeed,
		false);
}

// Reload weapon
void AWeaponBase::Reload()
{
	CurrentAmmoAmount = MaxAmmoAmount;
	WeaponReloaded.Broadcast();
}

// Returns if fire be executed
bool AWeaponBase::CanFire() const
{
	return CurrentAmmoAmount > 0;
}

// Consumes ammo
void AWeaponBase::ConsumeAmmo(const int AmmoConsumption)
{
	CurrentAmmoAmount -= AmmoConsumption;
}
