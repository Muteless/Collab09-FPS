// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interfaces/WeaponInput.h"

#include "Components/SkeletalMeshComponent.h"
#include "Weapon/GunBase.h"
#include "Weapon/MeleeBase.h"

#include "WeaponBase.generated.h"

UCLASS(Abstract)
class COLLAB09FPS_API AWeaponBase : public AActor,
public IWeaponInput
{
public:
	// Sets default values for this actor's properties
	AWeaponBase();
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	TSubclassOf<AGunBase> GunWeaponClass;

	UPROPERTY()
	AGunBase* GunWeaponInstance;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	TSubclassOf<AMeleeBase> MeleeWeaponClass;

	UPROPERTY()
	AMeleeBase* MeleeWeaponInstance;

	UFUNCTION(BlueprintCallable)
	void Initialize();
	
	void WeaponFire_Implementation() override;
	void WeaponReload_Implementation() override;
	void WeaponReloadInterrupt_Implementation() override;
	void WeaponSwitch_Implementation() override;
	bool GetWeaponMode_Implementation();

	void SetWeaponModeToGun();
	void SetWeaponModeToMelee();
	
protected:
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	bool bGunMode;

#pragma region Internal Attributes
	UPROPERTY()
	FName Name;

	UPROPERTY()
	USkeletalMeshComponent* Mesh;
	
#pragma endregion Internal Attributes
	
private:
	GENERATED_BODY()
};
