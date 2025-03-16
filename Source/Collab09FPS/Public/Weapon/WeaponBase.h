// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interfaces/WeaponInput.h"

#include "Components/SkeletalMeshComponent.h"
#include "Weapon/GunBase.h"

#include "WeaponBase.generated.h"

UCLASS(Abstract)
class COLLAB09FPS_API AWeaponBase : public AActor
{
public:
	// Sets default values for this actor's properties
	AWeaponBase();

	UFUNCTION()
	void WeaponFire_Implementation();

	UFUNCTION()
	void WeaponReload_Implementation();

protected:
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite)
	TArray<TSubclassOf<AGunBase>> GunClass;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	bool bGunMode;
	
private:
	GENERATED_BODY()
};
