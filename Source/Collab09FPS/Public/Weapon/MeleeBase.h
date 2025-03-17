// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeleeBase.generated.h"

UCLASS()
class COLLAB09FPS_API AMeleeBase : public AActor
{
public:
	// Sets default values for this actor's properties
	AMeleeBase();

	UFUNCTION()
	USkeletalMesh* GetWeaponMesh();
	
	UFUNCTION()
	void SetMeshVisibility(bool bVisibility);

	UFUNCTION()
	void Melee();

	UFUNCTION()
	bool CanMelee();

	UFUNCTION()
	void StartUpMeleePhase();

	UFUNCTION()
	void ActiveMeleePhase();

	UFUNCTION()
	void RecoveryPhase();

	UFUNCTION()
	void Initialize();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float StartUpFrames;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float ActiveFrames;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	float RecoveryFrames;
	
private:
	GENERATED_BODY()
	
};
