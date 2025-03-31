// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interfaces/WeaponInput.h"
#include "AbilitySystemInterface.h"

#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "Components/ArrowComponent.h"
#include "WeaponData/MeleeAssetData.h"
#include "WeaponData/GunAssetData.h"

#include "WeaponBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToFireNotEnoughAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToFireReloading);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToFireInBetweenROF);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponAmmoConsumed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponReloaded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponMelee);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToMelee);

UCLASS(Abstract)
class COLLAB09FPS_API AWeaponBase : public AActor,
public IWeaponInput
{
public:
	
	#pragma region Delegates
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWeaponFire OnWeaponFire;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWeaponFailedToFireNotEnoughAmmo OnWeaponFailedToFireNotEnoughAmmo;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWeaponFailedToFireReloading OnWeaponFailedToFireReloading;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWeaponFailedToFireInBetweenROF OnWeaponFailedToFireInBetweenROF;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWeaponAmmoConsumed OnWeaponAmmoConsumed;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWeaponReloaded OnWeaponReloaded;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWeaponMelee OnWeaponMelee;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWeaponFailedToMelee OnWeaponFailedToMelee;
	
	#pragma endregion Delegates
	
	// Sets default values for this actor's properties
	AWeaponBase();
	
	UFUNCTION(BlueprintCallable)
	void Initialize();

	virtual void WeaponPrimaryAction_Implementation() override;

	UPROPERTY()
	UAbilitySystemComponent* OwnerActorASC;

	UPROPERTY(VisibleAnywhere,
		BlueprintReadWrite)
	UArrowComponent* ProjectileSpawnLocation;
	
	#pragma region GunMode
		
		virtual void WeaponFire_Implementation() override;
		void RateOfFireTimerEnded();
		bool CanFire();
		bool EnoughAmmoToShoot() const;
		bool WeaponFireOnCooldown() const;
		void ConsumeAmmo();
		FTimerHandle RateOfFireTimerHandle;

		virtual void WeaponReload_Implementation() override;
		bool CanReload();
		void ReloadFinished();
		FTimerHandle ReloadTimerHandle;

	#pragma endregion GunMode

	#pragma region MeleeMode
		virtual void WeaponMelee_Implementation();
		bool CanMelee();

	#pragma endregion MeleeMode

	UPROPERTY(BlueprintReadOnly)
	FName Name;
	
	virtual void WeaponReloadInterrupt_Implementation() override;
	virtual void WeaponSwitch_Implementation() override;
	virtual bool GetWeaponMode_Implementation() override;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	UGunAssetData* GunAssetData;
	void SetupGunVariables();
	void SetWeaponModeToGun();

	UFUNCTION(BlueprintPure)
	TSubclassOf<ABulletBase> GetProjectile() const;
	UFUNCTION(BlueprintPure)
	int GetCurrentAmmo() const;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	UMeleeAssetData* MeleeAssetData;
	void SetupMeleeVariables();
	void SetWeaponModeToMelee();

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	bool bGunMode;

protected:
	UPROPERTY(VisibleAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	USkeletalMeshComponent* Mesh;

#pragma region Internal Attributes

#pragma region Melee
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Melee Mode")
	UAnimMontage* MeleeToGunSwitchAnimation;

	UPROPERTY()
	TArray<TSubclassOf<UGameplayEffect>> OnHitGameplayEffects;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Melee Mode")
	TArray<TSubclassOf<UGameplayEffect>> OnHitEffects;
	
	UPROPERTY()
	TArray<UAnimMontage*> MeleeAnimations;
	
	UPROPERTY()
	float MeleeDamage;
	
#pragma endregion Melee

#pragma region Gun
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Gun Mode")
	UAnimMontage* GunToMeleeSwitchAnimation;
	
	UPROPERTY()
	TArray<TSubclassOf<ABulletBase>> Projectiles;

	UPROPERTY(EDitAnywhere,
		BlueprintReadWrite,
		Category = "Gun Mode")
	float CurrentProjectileIndex;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Gun Mode")
	UAnimMontage* GunReloadAnimation;
	
	UPROPERTY()
	float GunDamage;

	UPROPERTY()
	float RateOfFire;

	UPROPERTY()
	int MagazineSize;

	UPROPERTY()
	int CurrentAmmo;

	UPROPERTY()
	int AmmoPerShot;

	UPROPERTY()
	float ReloadTime;
	
#pragma endregion Gun

#pragma endregion Internal Attributes
	
private:
	GENERATED_BODY()
};
