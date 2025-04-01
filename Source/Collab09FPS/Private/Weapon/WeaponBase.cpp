// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"

#include "Projectile/ProjectileBase.h"

// Sets default values
AWeaponBase::AWeaponBase():
	bGunMode(false)
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

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
			Projectiles = GunAssetData->Projectiles;
		}

		if (GunAssetData->GunReloadAnimation)
		{
			GunReloadAnimation = GunAssetData->GunReloadAnimation;
		}

		// Get ammo per shot from projectile
		if (Projectiles[CurrentProjectileIndex]->IsValidLowLevel())
		{
			AmmoPerShot = Projectiles[CurrentProjectileIndex].GetDefaultObject()->AmmoConsumedOnShot;
		}
		else
		{
			AmmoPerShot = 1;
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
		this->Destroy();
	}
}

void AWeaponBase::SetupMeleeVariables()
{
	if (MeleeAssetData != nullptr)
	{
		MeleeDamage = MeleeAssetData->Damage;

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
	
	ABulletBase* BulletSpawned = GetWorld()->SpawnActor<ABulletBase>(ProjectileClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams);

	BulletSpawned->SetOwner(GetOwner());
	BulletSpawned->Initialize();
	
	AmmoPerShot = BulletSpawned->AmmoConsumedOnShot;
	ConsumeAmmo();
	
	#pragma endregion SpawnProjectile

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
	UE_LOG(LogTemp, Warning, TEXT("CurrentAmmo: %i"), CurrentAmmo);

	// reload if we are out of ammo
	if (CurrentAmmo == 0)
	{
		Execute_WeaponReload(this);
	}
	
	OnWeaponAmmoConsumed.Broadcast();
}

void AWeaponBase::WeaponReload_Implementation()
{
	// Start Timer
	GetWorld()->GetTimerManager().SetTimer(
		ReloadTimerHandle,
		this,
		&AWeaponBase::ReloadFinished,
		ReloadTime,
		false);
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

void AWeaponBase::WeaponSwitch_Implementation()
{
	bGunMode = !bGunMode;

	if (bGunMode)
	{
		SetWeaponModeToGun();
	}
	else
	{
		SetWeaponModeToMelee();
	}
}

bool AWeaponBase::GetWeaponMode_Implementation()
{
	return bGunMode;
}

void AWeaponBase::SetWeaponModeToGun()
{
	// Gun mesh
	if (GunAssetData != nullptr && GunAssetData->Mesh)
	{
		Mesh->SetSkeletalMesh(GunAssetData->Mesh);
	}
}

TSubclassOf<ABulletBase> AWeaponBase::GetProjectile() const
{
	return Projectiles[CurrentProjectileIndex];
}

int AWeaponBase::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

void AWeaponBase::SetWeaponModeToMelee()
{
	// Melee mesh
	if (MeleeAssetData != nullptr && MeleeAssetData->Mesh)
	{
		Mesh->SetSkeletalMesh(MeleeAssetData->Mesh);
	}
}
