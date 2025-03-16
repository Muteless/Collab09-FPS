// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TimerManager.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile/BulletBase.h"

#include "GunBase.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFired);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToFireNoAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToFireReloading);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoConsumed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponStartedReload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToReloadFullMagazine);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToReload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponReloaded);

UCLASS(Abstract)
class COLLAB09FPS_API AGunBase : public AActor
{
public:
	// Sets default values for this actor's properties
	AGunBase();

	UFUNCTION(BlueprintCallable)
	void Initialize();
	
	UFUNCTION(BlueprintCallable)
	void Fire(bool bIncrementCurrentIndex);
	
	UFUNCTION(BlueprintPure)
	bool CanFire() const;

	UFUNCTION(BlueprintPure)
	bool HasAmmo() const;

	UFUNCTION(BlueprintCallable)
	void ConsumeAmmo(const int AmmoAmountToConsume);

	UFUNCTION(BlueprintCallable)
	void StartReload();

	UFUNCTION(BlueprintPure)
	bool IsReloading() const;
	
	UFUNCTION(BlueprintCallable)
	void FinishReload();
	
	UFUNCTION(BlueprintPure)
	bool CanReload() const;
	
	// Delegates, We want these public so UI or other actors can access it
	// Called when weapon fires
	UPROPERTY(BlueprintAssignable)
	FOnWeaponFired WeaponFired;

	// Called when weapon fails to fire because we have no ammo left
	UPROPERTY(BlueprintAssignable)
	FOnWeaponFailedToFireNoAmmo WeaponFailedToFireNoAmmo;

	// Called when weapon fails to fire because we are reloading
	UPROPERTY(BlueprintAssignable)
	FOnWeaponFailedToFireReloading WeaponFailedToFireReloading;
	
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

	// Called when weapon has failed to reload
	UPROPERTY(BlueprintAssignable)
	FOnWeaponFailedToReloadFullMagazine WeaponFailedToReloadFullMagazine;

protected:
	// Location object used when spawning the projectile
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* ProjectileSpawnLocation;

	// Skeletal mesh used by the weapon
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float RateOfFire;
	FTimerHandle RateOfFireTimerHandle;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	TArray<TSubclassOf<class ABulletBase>> ProjectileClasses;
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	int CurrentProjectileIndex;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float MagazineSize;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float CurrentAmmo;

	bool bIsReloading;

private:
	GENERATED_BODY()
};
