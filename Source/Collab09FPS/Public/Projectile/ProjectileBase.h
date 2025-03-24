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
		Category = "Bullet | Components")
	USphereComponent* Collision;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Bullet | Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Bullet | Components")
	UStaticMeshComponent* ProjectileMesh;
	
	UPROPERTY(VisibleAnywhere,
		BlueprintReadWrite,
		Category = "Bullet | Components")
	UNiagaraComponent* NiagaraSystemComponent;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Bullet | Movement")
	float InitialMovementSpeed;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Bullet | Movement")
	float MaxMovementSpeed;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Bullet | Movement")
	float GravityScale;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Bullet | Rotation")
	bool RotationFollowsVelocity;
	
protected:
private:
	GENERATED_BODY()
};
