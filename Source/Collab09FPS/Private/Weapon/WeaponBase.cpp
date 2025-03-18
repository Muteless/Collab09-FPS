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

void AWeaponBase::SetupGunVariables()
{
	if (GunAssetData != nullptr)
	{
		if (!GunAssetData->Projectile.IsEmpty())
		{
			Projectile = GunAssetData->Projectile;
		}

		if (GunAssetData->GunReloadAnimation)
		{
			GunReloadAnimation = GunAssetData->GunReloadAnimation;
		}
		
		GunDamage = GunAssetData->Damage;
		AmmoPerShot = GunAssetData->AmmoPerShot;
		RateOfFire = GunAssetData->RateOfFire;
		MagazineSize = GunAssetData->MagazineSize;
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
			UE_LOG(LogTemp, Log, TEXT("Firing!"));
			EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.Fire"));
			OwnerActorASC->HandleGameplayEvent(EventData.EventTag, &EventData);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Melee!"));
		EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.Melee"));
		OwnerActorASC->HandleGameplayEvent(EventData.EventTag, &EventData);
	}
}

void AWeaponBase::WeaponFire_Implementation()
{
	
}

bool AWeaponBase::CanFire()
{
	return !WeaponFireOnCooldown() && EnoughAmmoToShoot();
}

bool AWeaponBase::EnoughAmmoToShoot() const
{
	if (CurrentAmmo < AmmoPerShot)
	{
		
	}
	return CurrentAmmo > AmmoPerShot;
}

bool AWeaponBase::WeaponFireOnCooldown() const
{
	return !GetWorld()->GetTimerManager().IsTimerActive(RateOfFireTimerHandle);
}

void AWeaponBase::WeaponReload_Implementation()
{
	
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

void AWeaponBase::SetWeaponModeToGun()
{
	// Gun mesh
	if (GunAssetData != nullptr && GunAssetData->Mesh)
	{
		Mesh->SetSkeletalMesh(GunAssetData->Mesh);
	}
}

void AWeaponBase::SetWeaponModeToMelee()
{
	// Melee mesh
	if (MeleeAssetData != nullptr && MeleeAssetData->Mesh)
	{
		Mesh->SetSkeletalMesh(MeleeAssetData->Mesh);
	}
}
