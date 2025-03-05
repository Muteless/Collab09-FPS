// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// GAS
#include "GameplayEffect.h"

// Components
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"

#include "ProjectileBase.generated.h"

/**
 * @class AProjectileBase
 * @brief Abstract base class representing a generic projectile in the game.
 *
 * This class provides functionality to handle the visual and movement components
 * of a projectile as well as the application of gameplay effects to target actors.
 * It serves as a foundation for more specialized projectile types.
 */

UCLASS(Abstract)
class COLLAB09FPS_API AProjectileBase : public AActor
{
public:
	// Sets default values for this actor's properties
	AProjectileBase();

	// Apply gameplay effect
	void ApplyGameplayEffect(AActor* Target) const;
	
	// Called when the collision component hits anything
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& Hit);

protected:
	// Sphere collision component
	UPROPERTY(VisibleAnywhere,
		Category="Projectile | Collision | ")
	USphereComponent* CollisionComponent;
	
	// Projectile mesh
	UPROPERTY(EditAnywhere,
		Category="Projectile | Visual | ")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile | Visual | ")
	UNiagaraComponent* VfxComponent;
	
	// Projectile movement component
	UPROPERTY(VisibleAnywhere,
		Category="Projectile | Movement | ")
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	// Gameplay Effect class to apply
	UPROPERTY(EditAnywhere,
			  BlueprintReadWrite,
			  Category = "Projectile | Effects")
	TSubclassOf<class UGameplayEffect> GameplayEffectClass;

private:
	GENERATED_BODY()
};
