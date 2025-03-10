// Fill out your copyright notice in the Description page of Project Settings.

#include "Collab09FPS/Public/Character/CharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"

// Constructor
ACharacterBase::ACharacterBase()
{
	//* Ability System Component *//
	// Create AbilitySystemComponent
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	// Wall capsule component
	WallCapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Wall Capsule Collision"));
	WallCapsuleCollision->SetupAttachment(GetCapsuleComponent());
	WallCapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WallCapsuleCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	WallCapsuleCollision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	WallCapsuleCollision->SetGenerateOverlapEvents(true);
	
	WallCapsuleCollision->ShapeColor = FColor::Blue;
	WallCapsuleCollision->SetLineThickness(1);
	WallCapsuleCollision->SetCapsuleSize(GetCapsuleComponent()->GetScaledCapsuleRadius() + WallCapsuleDetectionOffsetRadius, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	
	
	// Create attribute sets
	HealthAttributeSet = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("Health Attribute Set"));
	AirActionAttributeSet = CreateDefaultSubobject<UAirActionAttributeSet>(TEXT("AirAction Attribute Set"));
	DashAttributeSet = CreateDefaultSubobject<UDashAttributeSet>(TEXT("Dash Attribute Set"));
	CMCAttributeSet = CreateDefaultSubobject<UCMCAttributeSet>(TEXT("CMC Attribute Set"));
	InitCharacterMovementComponent();
}

// AbilitySystemComponent interface, return ability system component
UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


// Get character movement component
UCharacterMovementComponent* ACharacterBase::ActorCharacterMovementComponent_Implementation()
{
	return GetCharacterMovement();
}

FVector ACharacterBase::GetMovementInput_Implementation()
{
	return GetLastMovementInputVector();
}

void ACharacterBase::CharacterMovementMove_Implementation(FVector MoveInput)
{
	AddMovementInput(GetActorRightVector(), MoveInput.X, false);
	AddMovementInput(GetActorForwardVector(), MoveInput.Y, false);
}

// Called when character has been possessed
void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Initialize wall capsule collision
	if (WallCapsuleCollision)
	{
		// Begin & end overlap events
		WallCapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &ACharacterBase::OnWallCapsuleBeginOverlap);
		WallCapsuleCollision->OnComponentEndOverlap.AddDynamic(this, &ACharacterBase::OnWallCapsuleEndOverlap);
	}
	
	// Initialize AbilitySystemComponent
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		
		// Set initial character attribute sets
		AddInitialCharacterAttributeSets();
		
		// Add initial character abilities to ability system
		AddInitialCharacterAbilities();

		// Add initial effects to ability system
		AddInitialCharacterGameplayEffects();
	}
}

void ACharacterBase::AddInitialCharacterAttributeSets()
{
	if (AbilitySystemComponent)
	{
		// Initialize attribute sets
		// Health
		AbilitySystemComponent->InitStats(UHealthAttributeSet::StaticClass(),
			CharacterAttributeDataTable);

		// Air Actions
		AbilitySystemComponent->InitStats(UAirActionAttributeSet::StaticClass(),
			CharacterAttributeDataTable);

		// Dash
		AbilitySystemComponent->InitStats(UDashAttributeSet::StaticClass(),
			CharacterAttributeDataTable);

		// CMC
		AbilitySystemComponent->InitStats(UCMCAttributeSet::StaticClass(),
			CharacterMovementAttributeDataTable);
	}
}

void ACharacterBase::InitCharacterMovementComponent() const
{
	GetCharacterMovement()->Mass = CMCAttributeSet->Mass.GetBaseValue();
	GetCharacterMovement()->MaxWalkSpeed = CMCAttributeSet->MaxWalkSpeed.GetBaseValue();
	GetCharacterMovement()->MaxAcceleration = CMCAttributeSet->MaxAcceleration.GetBaseValue();
	GetCharacterMovement()->MaxWalkSpeedCrouched = CMCAttributeSet->MaxWalkSpeedCrouched.GetBaseValue();
	GetCharacterMovement()->MinAnalogWalkSpeed = CMCAttributeSet->MinAnalogWalkSpeed.GetBaseValue();
	GetCharacterMovement()->GroundFriction = CMCAttributeSet->GroundFriction.GetBaseValue();
	GetCharacterMovement()->bUseSeparateBrakingFriction = CMCAttributeSet->bUseSeparateBrakingFactor.GetBaseValue();
	GetCharacterMovement()->BrakingFrictionFactor = CMCAttributeSet->BrakingFrictionFactor.GetBaseValue();
	GetCharacterMovement()->BrakingFriction = CMCAttributeSet->BrakingFriction.GetBaseValue();
	GetCharacterMovement()->BrakingDecelerationWalking = CMCAttributeSet->BrakingDecelerationWalking.GetBaseValue();
	GetCharacterMovement()->BrakingDecelerationFalling = CMCAttributeSet->BrakingDecelarationFalling.GetBaseValue();
	GetCharacterMovement()->MaxStepHeight = CMCAttributeSet->MaxStepHeight.GetBaseValue();
	GetCharacterMovement()->SetWalkableFloorAngle(CMCAttributeSet->WalkableFloorAngle.GetBaseValue());
	GetCharacterMovement()->CrouchedHalfHeight = CMCAttributeSet->CrouchedHalfHeight.GetBaseValue();
	GetCharacterMovement()->GravityScale = CMCAttributeSet->GravityScale.GetBaseValue();
	GetCharacterMovement()->JumpZVelocity = CMCAttributeSet->JumpZVelocity.GetBaseValue();
	GetCharacterMovement()->AirControl = CMCAttributeSet->AirControl.GetBaseValue();
	GetCharacterMovement()->AirControlBoostMultiplier = CMCAttributeSet->AirControlBoostMultiplier.GetBaseValue();
	GetCharacterMovement()->AirControlBoostVelocityThreshold = CMCAttributeSet->AirControlBoostVelocityThreshold.GetBaseValue();
	GetCharacterMovement()->FallingLateralFriction = CMCAttributeSet->FallingLateralFriction.GetBaseValue();
}

// Add initial character abilities
void ACharacterBase::AddInitialCharacterAbilities()
{
	if (AbilitySystemComponent)
	{
		for (TSubclassOf<UGameplayAbility> Ability : InitialAbilities)
		{
			// if ability is valid
			if (Ability != nullptr)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
			}
		}
	}
}


void ACharacterBase::AddInitialCharacterGameplayEffects()
{
	if (AbilitySystemComponent)
	{
		for (TSubclassOf<UGameplayEffect> GameplayEffect : InitialGameplayEffects)
		{
			// Create an outgoing spec for the Gameplay Effect
			FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect,1.f, AbilitySystemComponent->MakeEffectContext());
			
			// Apply the effect to the Ability System Component
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}
	}
}

// Make the character ground jump
void ACharacterBase::CharacterMovementJump_Implementation()
{
	Jump();
}

// Air jump
void ACharacterBase::CharacterMovementAirJump_Implementation()
{
	// Reset Z Velocity
	GetCharacterMovement()->Velocity.Z = 0.0f;
	
	// Add jump impulse
	GetCharacterMovement()->AddImpulse(FVector(0.0f,
		0.0f,
		(GetCharacterMovement()->JumpZVelocity)),
		true);
}


void ACharacterBase::OnWallCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	UCharacterMovementComponentBase* MovementComponent = Cast<UCharacterMovementComponentBase>
		(GetCharacterMovement());
	
	// Movement class is valid
	if (MovementComponent)
	{
		// Other actor is valid and it is not this class
		if (OtherActor && OtherActor != this)
		{
			if (MovementComponent->CanWallRun() && AbilitySystemComponent)
			{
				// Create a gameplay event payload
				FGameplayEventData EventData;
				EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.WallRun"));
				
				AbilitySystemComponent->HandleGameplayEvent(EventData.EventTag, &EventData);
			}
		}
	}
}

void ACharacterBase::OnWallCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		
	}
}

void ACharacterBase::CharacterMovementWallRun_Implementation()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}

void ACharacterBase::CharacterMovementEndWallRun_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("WallRunEnd"))
	if (AbilitySystemComponent)
	{
		// Create a gameplay event payload
		FGameplayEventData EventData;
		EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.WallRunEnd"));
		
		AbilitySystemComponent->HandleGameplayEvent(EventData.EventTag, &EventData);
	}
}

// On landed
void ACharacterBase::Landed(const FHitResult& Hit)
{
	Execute_CharacterMovementLanded(this);
	Super::Landed(Hit);
}

void ACharacterBase::CharacterMovementLanded_Implementation()
{
	if (AbilitySystemComponent)
	{
		for (TSubclassOf<UGameplayEffect> Effect : OnLandedEffects)
		{
			// Create an outgoing spec for the Gameplay Effect
			FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1.f, AbilitySystemComponent->MakeEffectContext());
			
			// Apply the effect to the Ability System Component
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}
	}
}

// Ground Dash
void ACharacterBase::CharacterMovementGroundDash_Implementation()
{
	if (AbilitySystemComponent)
	{
		// Define optional event data
		FGameplayEventData Payload;
	
		// Use dash ability event
		AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Ability.GroundDash")), &Payload);
	}
}

void ACharacterBase::CharacterMovementAirDash_Implementation()
{
	if (AbilitySystemComponent)
	{
		// Define optional event data
		FGameplayEventData Payload;
	
		// Use dash ability event
		AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Ability.AirDash")), &Payload);
	}
}

//* Blueprint Helper functions *//
// Get current health attribute
float ACharacterBase::GetCurrentHealth() const
{
	if (HealthAttributeSet)
	{
		return HealthAttributeSet->GetCurrentHealth();
	}
	return -1.0f;
}

// Get max health
float ACharacterBase::GetMaxHealth() const
{
	if (HealthAttributeSet)
	{
		return HealthAttributeSet->GetMaxHealth();
	}
	return -1.0f;
}

// Get character is airborne
bool ACharacterBase::IsAirborne_Implementation()
{
	return GetCharacterMovement()->IsFalling();
}

// Get current air actions
float ACharacterBase::GetCurrentAirActions() const
{
	if (AirActionAttributeSet)
	{
		return AirActionAttributeSet->GetCurrentAirActions();
	}
	return -1.0f;
}

// Get max air actions
float ACharacterBase::GetMaxAirActions() const
{
	if (AirActionAttributeSet)
	{
		return AirActionAttributeSet->GetMaxAirActions();
	}
	return -1.0f;
}
