// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Collab09FPS/Public/Projectile/ProjectileBase.h"
#include "GameFramework/Actor.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile/ProjectileBase.h"
#include "GameplayAbilities/Public/AbilitySystemInterface.h"
#include "GAS/AbilitySystemComponentBase.h"

#include "WeaponBase.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFired);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToFire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoConsumed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponStartedReload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponReloaded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToReload);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponMelee);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToMelee);

/**
 * @class AWeaponBase
 * @brief Represents an abstract base class for weapon functionality in the game.
 *
 * The AWeaponBase class provides core functionalities for weapons, including firing, reloading, and melee attacks.
 * It includes properties for ammo, rate of fire, and reload speed, as well as delegate events for responding to
 * weapon-related actions. The class is also designed to be used as a base for other weapon implementations.
 */

UCLASS(Abstract)
class COLLAB09FPS_API AWeaponBase : public AActor, public IAbilitySystemInterface
{
public:
	// Sets default values for this actor's properties
	AWeaponBase();

	// Ability system component
	virtual UAbilitySystemComponentBase* GetAbilitySystemComponent();
	
	// Delegates, We want these public so UI or other actors can access it
	// Called when weapon fires
	UPROPERTY(BlueprintAssignable)
	FOnWeaponFired WeaponFired;

	// Called when weapon fails to fire
	UPROPERTY(BlueprintAssignable)
	FOnWeaponFailedToFire WeaponFailedToFire;

	// Called when ammo has been consumed
	UPROPERTY(BlueprintAssignable)
	FOnAmmoConsumed WeaponAmmoConsumed;

	// Called when a weapon has started to reload
	UPROPERTY(BlueprintAssignable)
	FOnWeaponStartedReload WeaponStartedReload;
	
	// Called when a weapon has reloaded
	UPROPERTY(BlueprintAssignable)
	FOnWeaponReloaded WeaponReloaded;

	// Called when weapon has failed to reload
	UPROPERTY(BlueprintAssignable)
	FOnWeaponFailedToReload WeaponFailedToReload;
	
	// Called when weapon has used melee attack
	UPROPERTY(BlueprintAssignable)
	FOnWeaponMelee WeaponMelee;

	// Called when weapon has failed to melee attack
	UPROPERTY(BlueprintAssignable)
	FOnWeaponFailedToMelee WeaponFailedToMelee;

protected:
	// Projectile class used when firing
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Weapon | Firing | Projectile | ")
	TArray<TSubclassOf<class AProjectileBase>> ProjectileClasses;
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Weapon | Firing | Projectile | ")
	int CurrentProjectileIndex;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Weapon | Melee | ")
	TArray<TSubclassOf<class UMeleeAbilityBase>> MeleeAbilityClasses;
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Weapon | Melee | ")
	int CurrentMeleeAbilityIndex;

	// Location object used when spawning the projectile
	UPROPERTY(VisibleAnywhere,
		meta=(DisplayName="Projectile Spawn Location"),
		Category="Weapon | Firing | Projectile | ")
	UArrowComponent* ProjectileSpawnLocation;

	// Skeletal mesh used by the weapon
	UPROPERTY(VisibleAnywhere,
		meta=(DisplayName="Weapon Mesh"),
		Category="Weapon | ")
	class USkeletalMeshComponent* WeaponMesh;
	
	// Rate of fire (per Second)
	UPROPERTY(BlueprintReadWrite,
		meta=(DisplayName="Rate Of Fire"),
		Category="Weapon | Firing | ")
	float BaseRateOfFire = 1;
	float RateOfFire;
	FTimerHandle RateOfFireTimerHandle;
	
	// Reloading speed in seconds
	UPROPERTY(BlueprintReadWrite,
		meta=(DisplayName="Reload Speed"),
		Category="Weapon | Firing | Reloading | ")
	float BaseReloadSpeed = 1;
	float ReloadSpeed;
	FTimerHandle ReloadTimerHandle;
	
	// Max ammo count
	UPROPERTY(BlueprintReadWrite,
		meta=(DisplayName="Max Ammo"),
		Category="Weapon | Firing | Ammo | ")
	float MaxAmmoAmount = 10;
	float CurrentAmmoAmount;
	
	// Function to shoot projectile
	UFUNCTION(BlueprintCallable,
		Category="Weapon | Firing | ")
	void Fire(int AmmoConsumption, bool bIncrementCurrentIndex);
	bool CanFire() const;
	
	// Current ammo minus ammo consumption
	UFUNCTION(BlueprintCallable,
		Category="Weapon | Firing | Ammo | ")
	void ConsumeAmmo(const int AmmoConsumption);
	
	// Function to melee attack
	UFUNCTION(BlueprintCallable)
	TSubclassOf<UMeleeAbilityBase> Melee(const bool bIncrementCurrentIndex);
	bool CanMelee() const;

	// Function to start reloading weapon
	UFUNCTION(BlueprintCallable,
		Category="Weapon | Firing | ")
	void Reload();
	void ReloadComplete();
	bool CanReload() const;
	
private:
	GENERATED_BODY()
};