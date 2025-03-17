// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/MeleeBase.h"

// Sets default values
AMeleeBase::AMeleeBase()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	// Melee mesh
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
}

USkeletalMesh* AMeleeBase::GetWeaponMesh()
{
	return WeaponMesh->GetSkeletalMeshAsset();
}

void AMeleeBase::SetMeshVisibility(bool bVisibility)
{
	WeaponMesh->SetVisibility(bVisibility);
}

void AMeleeBase::Initialize()
{
	SetMeshVisibility(false);
}
