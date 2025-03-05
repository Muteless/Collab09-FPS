// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Collab09FPS/Public/Projectile/ProjectileBase.h"
#include "GameFramework/Actor.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile/ProjectileBase.h"

#include "WeaponBase.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFired);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponReloaded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMelee);


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

	// Called when a weapon has used melee attack (Weapon melee delegate)
	UPROPERTY(BlueprintAssignable)
	FWeaponReloaded OnMelee;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Weapon | Firing | Projectile")
	TSubclassOf<class AProjectileBase> ProjectileClass;

	// Location used when spawning the projectile
	UPROPERTY(VisibleAnywhere,
		meta=(DisplayName="Projectile Spawn Location"),
		Category="Weapon | Firing | Projectile")
	UArrowComponent* ProjectileSpawnLocation;

	// Skeletal mesh used by the weapon
	UPROPERTY(VisibleAnywhere,
		meta=(DisplayName="Weapon Mesh"),
		Category="Weapon | ")
	class USkeletalMeshComponent* WeaponMesh;
	
	// Rate of fire (per Second)
	UPROPERTY(BlueprintReadWrite,
		meta=(DisplayName="Rate Of Fire"),
		Category="Weapon | Firing |")
	float BaseRateOfFire;
	float RateOfFire;
	
	// Reloading speed in seconds
	UPROPERTY(BlueprintReadWrite,
		meta=(DisplayName="Reload Speed"),
		Category="Weapon | Firing |")
	float BaseReloadSpeed;
	float ReloadSpeed;

	// Max ammo count
	UPROPERTY(BlueprintReadWrite,
		meta=(DisplayName="Max Ammo"),
		Category="Weapon | Firing |")
	float MaxAmmoAmount;
	float CurrentAmmoAmount;

	
	
	// Function to shoot projectile
	UFUNCTION(BlueprintCallable)
	void Fire();

	// Function to melee attack
	UFUNCTION(BlueprintCallable)
	static void Melee();

	// Function to reload weapon
	UFUNCTION(BlueprintCallable)
	static void Reload();
	
private:
	GENERATED_BODY()
	
};
