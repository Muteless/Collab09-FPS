// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/ProjectileBase.h"
#include "NiagaraComponent.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
	ProjectileMovementComponent = nullptr;
	ProjectileMesh = nullptr;
	NiagaraSystemComponent = nullptr;
	Collision = nullptr;
	InitialMovementSpeed = 3500.0;
	MaxMovementSpeed = 3500.0;
	RotationFollowsVelocity = true;
	
	
	// Create the Sphere Collision Component
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(10.0f);
	
	Collision->SetCollisionProfileName(TEXT("Projectile"));
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetNotifyRigidBodyCollision(true);
	SetRootComponent(Collision);

	// Create the Static Mesh Component
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(Collision);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	// Create the Niagara component
	NiagaraSystemComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara System Component"));
	NiagaraSystemComponent->SetupAttachment(RootComponent);
	
	// Create the Projectile Movement Component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = InitialMovementSpeed;
	ProjectileMovementComponent->MaxSpeed = MaxMovementSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = RotationFollowsVelocity;
	ProjectileMovementComponent->ProjectileGravityScale = GravityScale;
}

void AProjectileBase::Initialize()
{
	if (GetOwner()->GetOwner())
	{
		Collision->IgnoreActorWhenMoving(GetOwner()->GetOwner(), true);
		UE_LOG(LogTemp, Warning, TEXT("ProjectileBase::Initialize() owner: %s"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ProjectileBase::Initialize() no owner's owner"));
	}
}
