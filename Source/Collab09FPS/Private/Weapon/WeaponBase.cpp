// Fill out your copyright notice in the Description page of Project Settings.


#include "Collab09FPS/Public/Weapon/WeaponBase.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	// Default variables
	ProjectileClass = nullptr;
	RateOfFire = BaseRateOfFire;
	ReloadSpeed = BaseReloadSpeed;

	// Bind delegates
	
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}
