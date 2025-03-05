// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AbilitySystemComponentBase.h"
#include "Collab09FPS/Public/Projectile/ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Create collision component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Component"));
	
	// Set root component to be the collision component
	RootComponent = CollisionComponent;
	
	// Configure collision settings
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	
	// Create projectile mesh and attach to collision
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(CollisionComponent);

	// Create VFX component and attach to collision
	VfxComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VfxComponent"));
	VfxComponent->SetupAttachment(CollisionComponent);
	
	// Create ProjectileMovementComponent
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 100;
	ProjectileMovementComponent->MaxSpeed = 100;
}

// On collision hit
void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// when the projectile hits another object
	if (OtherActor && OtherActor != this && OtherComponent)
	{
		// Apply gameplay effect to the target
		ApplyGameplayEffect(OtherActor);
	}
}

void AProjectileBase::ApplyGameplayEffect(AActor* Target) const
{
	if (!Target || !GameplayEffectClass)
	{
		return;
	}

	// Check if the target has an AbilitySystemComponent
	UAbilitySystemComponent* TargetASC = Target->FindComponentByClass<UAbilitySystemComponentBase>();
	
	if (TargetASC)
	{
		// Create a gameplay effect spec handle
		FGameplayEffectContextHandle EffectContextHandle;
		FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);

		if (SpecHandle.IsValid())
		{
			// Apply the gameplay effect to the target
			TargetASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
		}
	}

}
