// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterBase.h"

#include "Collab09FPS/Collab09FPS.h"

#include "Components/CapsuleComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Interfaces/CharacterController.h"

// Constructor
APlayerCharacterBase::APlayerCharacterBase() :
WeaponSocketName("WeaponSocket")
{
	bUseControllerRotationYaw = true;
	
	// Attribute sets
	StaminaAttributeSet = CreateDefaultSubobject<UStaminaAttributeSet>(TEXT("Stamina Attribute Set"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	// Weapon location
	WeaponLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("WeaponLocation"));
	WeaponLocation->SetupAttachment(CameraComponent);
}

void APlayerCharacterBase::LoadData_Implementation(USaveGame* SaveGame)
{
	FPlayerData PlayerSaveData = ISaveGameInterface::Execute_GetPlayerSaveData(SaveGame);
	
		if (PlayerSaveData.HasWeapon)
		{
			SpawnWeapon();
		}

		if (WeaponInstance->IsValidLowLevel())
		{
			WeaponInstance->bGunMode = PlayerSaveData.bGunMode;
			WeaponInstance->GunAssetData = PlayerSaveData.GunAssetData;
			WeaponInstance->MeleeAssetData = PlayerSaveData.MeleeAssetData;
			WeaponInstance->Initialize();
		}
}

FPlayerData APlayerCharacterBase::MakePlayerSaveData()
{
	FPlayerData PlayerSaveData;

	if (WeaponInstance)
	{
		PlayerSaveData.HasWeapon = true;
		PlayerSaveData.bGunMode = WeaponInstance->bGunMode;
		PlayerSaveData.GunAssetData = WeaponInstance->GunAssetData;
		PlayerSaveData.MeleeAssetData = WeaponInstance->MeleeAssetData;
	}
	else
	{
		PlayerSaveData.HasWeapon = false;
		PlayerSaveData.bGunMode = true;
		PlayerSaveData.GunAssetData = nullptr;
		PlayerSaveData.MeleeAssetData = nullptr;
	}
	
	return PlayerSaveData;
}

void APlayerCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APlayerCharacterBase::SpawnWeapon()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	WeaponInstance = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass,
		SpawnParams);
	
	if (WeaponInstance)
	{
		WeaponInstance->AttachToComponent(
			WeaponLocation,
			FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		WeaponInstance->Initialize();
	}
}

void APlayerCharacterBase::AddInitialCharacterAttributeSets()
{
	Super::AddInitialCharacterAttributeSets();
	
	if (AbilitySystemComponent)
	{
		// Stamina
		AbilitySystemComponent->AddSet<UStaminaAttributeSet>();
	}
}

//* Blueprint Helper functions *//
// Get current stamina attribute
float APlayerCharacterBase::GetCurrentStamina() const
{
	if (StaminaAttributeSet)
	{
		return StaminaAttributeSet->GetCurrentStamina();
	}
	return -1.0f;
}