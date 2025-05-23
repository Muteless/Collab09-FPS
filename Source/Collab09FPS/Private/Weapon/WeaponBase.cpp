﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile/ProjectileBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	MeleeHitbox = CreateDefaultSubobject<UHitbox>(TEXT("MeleeHitbox"));

	ProjectileSpawnLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnLocation"));
	ProjectileSpawnLocation->SetupAttachment(Mesh);
	ProjectileSpawnLocation->ArrowSize = 0.5;
	ProjectileSpawnLocation->ArrowLength = 50;
}

void AWeaponBase::Initialize()
{
	AActor* OwnerActor = GetOwner();
	
	if (OwnerActor)
	{
		// Find the Ability System Component
		OwnerActorASC = OwnerActor->FindComponentByClass<UAbilitySystemComponent>();

		if (!OwnerActorASC)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("No Ability System Component found on weapon owner."));
		}
	}

	LevelGameState = GetWorld()->GetGameState<ALevelGameState>();
	if (LevelGameState)
	{
		switch (LevelGameState->WorldState)
		{
			case EWorldState::WorldOne:
				bGunMode = true;
				break;
			case EWorldState::WorldTwo:
				bGunMode = false;
				break;
		}
		
        // TODO: LevelGameState->OnWorldTransition.AddDynamic(this, &AWeaponBase::SwitchMode);
	}

	SetupGunVariables();
	SetupMeleeVariables();
	
	// Setup weapon mode
	if (bGunMode)
	{
		SetWeaponModeToGun();
	}
	else
	{
		SetWeaponModeToMelee();
	}
}

void AWeaponBase::SetupGunVariables()
{
	if (GunAssetData != nullptr)
	{
		if (!GunAssetData->Projectiles.IsEmpty())
		{
			// Get projectiles
			Projectiles = GunAssetData->Projectiles;
			
			// Get ammo per shot from projectile
			if (Projectiles[CurrentProjectileIndex]->IsValidLowLevel())
			{
				AmmoPerShot = Projectiles[CurrentProjectileIndex].GetDefaultObject()->AmmoConsumedOnShot;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Invalid Projectile Index or Class in GunAssetData."));
				AmmoPerShot = 1; // Fallback value
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Projectiles array is empty!"));
		}

		if (GunAssetData->GunReloadAnimation)
		{
			GunReloadAnimation = GunAssetData->GunReloadAnimation;
		}
		
		RateOfFire = GunAssetData->RateOfFire;
		MagazineSize = GunAssetData->MagazineSize;
		CurrentAmmo = GunAssetData->MagazineSize;
		ReloadTime = GunAssetData->ReloadTime;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GunAssetData is not set!"));
		UE_LOG(LogTemp, Error, TEXT("Destroying WeaponBase"))
		this->Destroy(); // This could be avoided for better error handling - dan
	}
}

void AWeaponBase::SetupMeleeVariables()
{
	if (MeleeAssetData != nullptr)
	{
		MeleeDamage = MeleeAssetData->Damage;
		MeleeHitbox->OnHitGameplayEffects = MeleeAssetData->OnHitGameplayEffects;

		if (!MeleeAssetData->MeleeAnimations.IsEmpty())
		{
			MeleeAnimations = MeleeAssetData->MeleeAnimations;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MeleeAssetData is not set!"));
		UE_LOG(LogTemp, Error, TEXT("Destroying WeaponBase"))
		this->Destroy();
	}
}

void AWeaponBase::WeaponPrimaryAction_Implementation()
{
	FGameplayEventData EventData;
	
	if (bGunMode)
	{
		if (CanFire())
		{
			EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.Fire"));
			OwnerActorASC->HandleGameplayEvent(EventData.EventTag, &EventData);
		}
	}
	else
	{
		EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.Melee"));
		OwnerActorASC->HandleGameplayEvent(EventData.EventTag, &EventData);
	}
}

void AWeaponBase::WeaponFire_Implementation()
{
	TSubclassOf<ABulletBase> ProjectileClass = Projectiles[CurrentProjectileIndex];
	if (!*ProjectileClass) // Validate if the class exists
	{
		UE_LOG(LogTemp,
			Error,
			TEXT("Projectile class at index %f is invalid!"),
			CurrentProjectileIndex);
		return;
	}

	#pragma region SpawnProjectile
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	
	FVector SpawnLocation = ProjectileSpawnLocation->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnLocation->GetComponentRotation();
	
	ABulletBase* BulletSpawned = GetWorld()->SpawnActor<ABulletBase>(
		ProjectileClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams);

	BulletSpawned->SetOwner(GetOwner());
	BulletSpawned->Initialize();

	// Spawn muzzle flash
	if (GunAssetData->MuzzleFlash)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(
			GunAssetData->MuzzleFlash,
			ProjectileSpawnLocation,
			FName("MuzzleFlash"),
			FVector(-50, 0, 0),
			FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset,
			true);
	}
	
	AmmoPerShot = BulletSpawned->AmmoConsumedOnShot;
	ConsumeAmmo();
	
	#pragma endregion SpawnProjectile

	// Play fire sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), GunAssetData->FireSound, GetActorLocation());
	
	// Start Timer
	GetWorld()->GetTimerManager().SetTimer(
		RateOfFireTimerHandle,
		this,
		&AWeaponBase::RateOfFireTimerEnded,
		RateOfFire,
		false);

	OnWeaponFire.Broadcast();
}

void AWeaponBase::RateOfFireTimerEnded()
{
	
}

bool AWeaponBase::CanFire()
{
	// Validate that the array has elements
	if (Projectiles.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile array is empty!"));
		return false;
	}

	// Ensure the index is valid
	if (!Projectiles.IsValidIndex(CurrentProjectileIndex))
	{
		UE_LOG(LogTemp,
			Error,
			TEXT("Invalid projectile index: %f! Check CurrentProjectileIndex."),
			CurrentProjectileIndex);
		return false;
	}
	
	return !WeaponFireOnCooldown() && EnoughAmmoToShoot();
}

bool AWeaponBase::EnoughAmmoToShoot() const
{
	return CurrentAmmo >= AmmoPerShot;
}

bool AWeaponBase::WeaponFireOnCooldown() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(RateOfFireTimerHandle);
}

void AWeaponBase::ConsumeAmmo()
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo - AmmoPerShot, 0, MagazineSize);
	
	// reload if we are out of ammo
	if (CurrentAmmo == 0)
	{
		Execute_WeaponReload(this);
	}
	
	OnWeaponAmmoConsumed.Broadcast();
}

void AWeaponBase::WeaponReload_Implementation()
{
	if (CanReload())
	{
		// Start Timer
		GetWorld()->GetTimerManager().SetTimer(
			ReloadTimerHandle,
			this,
			&AWeaponBase::ReloadFinished,
			ReloadTime,
			false);

		// Broadcast that we have started reloading
		OnWeaponStartReload.Broadcast();
	}
}

bool AWeaponBase::CanReload()
{
	return !GetWorldTimerManager().IsTimerActive(ReloadTimerHandle) && CurrentAmmo != MagazineSize;
}

void AWeaponBase::ReloadFinished()
{
	CurrentAmmo = MagazineSize;
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
	OnWeaponReloaded.Broadcast();
}

void AWeaponBase::WeaponMelee_Implementation()
{
	
}

bool AWeaponBase::CanMelee()
{
	return true;
}

void AWeaponBase::WeaponReloadInterrupt_Implementation()
{
	
}

void AWeaponBase::SwitchMode(EWorldState WorldState)
{
	UE_LOG(LogTemp, Warning, TEXT("Switching mode to %d"), WorldState);
	switch (WorldState)
	{
		case EWorldState::WorldOne:
			bGunMode = true;
			break;
		case EWorldState::WorldTwo:
			bGunMode = false;
			break;
	}
	
	if (bGunMode)
	{
		SetWeaponModeToGun();
		
	}
	else
	{
		SetWeaponModeToMelee();
	}
	
	OnWeaponModeSwitched.Broadcast();
}


bool AWeaponBase::GetWeaponMode_Implementation()
{
	return bGunMode;
}

void AWeaponBase::SetWeaponModeToGun()
{
	
}

TArray<TSubclassOf<ABulletBase>> AWeaponBase::GetProjectiles() const
{
	return Projectiles;
}

void AWeaponBase::SetWeaponModeToMelee()
{
	
}

TSubclassOf<ABulletBase> AWeaponBase::GetProjectile() const
{
	return Projectiles[CurrentProjectileIndex];
}

void AWeaponBase::SetProjectile(const TSubclassOf<ABulletBase> Projectile)
{
	CurrentProjectileIndex = Projectiles.Find(Projectile);
	OnWeaponProjectileChanged.Broadcast();
}

int AWeaponBase::GetMagazineSize() const
{
	return MagazineSize;
}

int AWeaponBase::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

float AWeaponBase::GetReloadTime() const
{
	return ReloadTime;
}

