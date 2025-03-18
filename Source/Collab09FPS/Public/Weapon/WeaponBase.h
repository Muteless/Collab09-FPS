// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interfaces/WeaponInput.h"
#include "AbilitySystemInterface.h"

#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "WeaponData/MeleeAssetData.h"
#include "WeaponData/GunAssetData.h"

#include "WeaponBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToFireNotEnoughAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToFireReloading);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFailedToFireInBetweenROF);
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
	
#pragma region GunMode
	virtual void WeaponFire_Implementation() override;
	bool CanFire();
	bool EnoughAmmoToShoot() const;
	bool WeaponFireOnCooldown() const;
	FTimerHandle RateOfFireTimerHandle;

	virtual void WeaponReload_Implementation() override;
	FTimerHandle ReloadTimerHandle;
	
#pragma endregion GunMode

#pragma region MeleeMode
	virtual void WeaponMelee_Implementation();
	bool CanMelee();

#pragma endregion MeleeMode
	
	
	virtual void WeaponReloadInterrupt_Implementation() override;
	virtual void WeaponSwitch_Implementation() override;
	virtual bool GetWeaponMode_Implementation() override;

	void SetupGunVariables();
	void SetWeaponModeToGun();

	void SetupMeleeVariables();
	void SetWeaponModeToMelee();
	
protected:
	UPROPERTY()
	FName Name;

	UPROPERTY()
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	UGunAssetData* GunAssetData;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	UMeleeAssetData* MeleeAssetData;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	bool bGunMode;

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
	TArray<TSubclassOf<ABulletBase>> Projectile;

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
