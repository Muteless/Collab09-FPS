// Fill out your copyright notice in the Description page of Project Settings.


#include "Collab09FPS/Public/Projectile/ProjectileBase.h"

#include "Projects.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
	// Create projectile mesh
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
		
	// Create ProjectileMovementComponent
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 100;
	ProjectileMovementComponent->MaxSpeed = 100;
}

