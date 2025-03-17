// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"


// Sets default values
AWeaponBase::AWeaponBase():
	GunWeaponInstance(nullptr),
	MeleeWeaponInstance(nullptr),
	bGunMode(false)
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AWeaponBase::Initialize()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	// Spawn the gun weapon at the root component's location
	GunWeaponInstance = GetWorld()->SpawnActor<AGunBase>(GunWeaponClass,
		GetActorTransform(),
		SpawnParams);

	// Spawn the melee weapon at the root component's location
	MeleeWeaponInstance = GetWorld()->SpawnActor<AMeleeBase>(MeleeWeaponClass,
		GetActorTransform(),
		SpawnParams);
	
	if (GunWeaponClass)
	{
		// Gun weapon instance
		if (GunWeaponInstance)
		{
			GunWeaponInstance->Initialize();
			
			// Attach gun instance to skeletal mesh
			GunWeaponInstance->AttachToComponent(Mesh,
				FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			UE_LOG(LogTemp, Warning, TEXT("GunWeapon instance spawned and attached"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn GunWeaponClass at: %s"),
				*GetOwner()->GetName());
		}
	}
	
	// Melee weapon instance
	if (MeleeWeaponInstance)
	{
		MeleeWeaponInstance->Initialize();
			
		MeleeWeaponInstance->AttachToComponent(Mesh,
			FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		UE_LOG(LogTemp, Warning, TEXT("MeleeWeapon instance spawned and attached"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn GunWeaponClass at: %s"),
			*GetOwner()->GetName());
	}
	
	if (bGunMode)
	{
		SetWeaponModeToGun();
	}
	else
	{
		SetWeaponModeToMelee();
	}
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
	if (GunWeaponInstance)
	{
		Mesh->SetSkeletalMesh(GunWeaponInstance->GetWeaponMesh());
	}
}

void AWeaponBase::SetWeaponModeToMelee()
{
	if (MeleeWeaponInstance)
	{
		Mesh->SetSkeletalMesh(MeleeWeaponInstance->GetWeaponMesh());
	}
}
