// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/MeleeBase.h"

// Sets default values
AMeleeBase::AMeleeBase()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	// Melee mesh
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	WeaponMesh->SetVisibility(false);
}

USkeletalMesh* AMeleeBase::GetWeaponMesh()
{
	return WeaponMesh->GetSkeletalMeshAsset();
}

void AMeleeBase::SetMeshVisibility(bool bVisibility)
{
	WeaponMesh->SetVisibility(bVisibility);
}

void AMeleeBase::Melee()
{
	if (CanMelee())
	{
		
	}
}

bool AMeleeBase::CanMelee()
{
	return true;
}

void AMeleeBase::StartUpMeleePhase()
{
	
}

void AMeleeBase::ActiveMeleePhase()
{
}

void AMeleeBase::RecoveryPhase()
{
}

void AMeleeBase::Initialize()
{
	SetMeshVisibility(false);
}
