// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "ProjectileBase.generated.h"

UCLASS(Abstract)
class COLLAB09FPS_API AProjectileBase : public AActor
{
public:
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Projectile mesh
	UPROPERTY(EditAnywhere,
		Category="Projectile | Visual | ")
	UStaticMeshComponent* ProjectileMesh;

	// Projectile movement component
	UPROPERTY(VisibleAnywhere,
		Category="Projectile | Movement | ")
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

private:
	GENERATED_BODY()
};
