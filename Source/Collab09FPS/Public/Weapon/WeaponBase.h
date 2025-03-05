// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiffResults.h"
#include "Collab09FPS/Public/Projectile/ProjectileBase.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFired);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponReloaded);


UCLASS(Abstract)
class COLLAB09FPS_API AWeaponBase : public AActor
{
public:
	// Sets default values for this actor's properties
	AWeaponBase();
	
	// Delegates, We want them public so UI or other actors can access it
	// Called when a weapon is fired (Weapon fired delegate)
	UPROPERTY(BlueprintAssignable)
	FWeaponFired WeaponFired;

	// Called when a weapon has reloaded (Weapon fired delegate)
	UPROPERTY(BlueprintAssignable)
	FWeaponReloaded WeaponReloaded;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Projectile class shot by the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | Firing")
	TSubclassOf<class AProjectileBase> ProjectileClass;
	
	// Rate of fire (per Second)
	UPROPERTY(BlueprintReadWrite, meta=(DisplayName="RateOfFire"), Category="Weapon | Firing")
	float BaseRateOfFire;
	float RateOfFire;
	

	// Reloading speed in seconds
	UPROPERTY(BlueprintReadWrite, meta=(DisplayName="ReloadSpeed"), Category="Weapon | Firing")
	float BaseReloadSpeed;
	float ReloadSpeed;
	
private:
	GENERATED_BODY()
	
};
