// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletBase.h"

#include "NiagaraSystem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "ProjectileBase.generated.h"

UCLASS(Abstract)
class COLLAB09FPS_API AProjectileBase : public ABulletBase
{
public:
	AProjectileBase();

	// Sphere collision component
	UPROPERTY(VisibleAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	USphereComponent* Collision;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	UStaticMeshComponent* ProjectileMesh;
	
	UPROPERTY(VisibleAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	UNiagaraComponent* NiagaraSystemComponent;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	float InitialMovementSpeed;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	float MaxMovementSpeed;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	float GravityScale;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	bool RotationFollowsVelocity;
	
protected:
private:
	GENERATED_BODY()
};
