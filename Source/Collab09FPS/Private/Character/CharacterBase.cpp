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


void ACharacterBase::InputActionMove_Implementation(const EInputTypes InputType, const FVector2D Input)
{
	switch (InputType)
	{
		default: return;
		case EInputTypes::Triggered:
			if (!AbilitySystemComponent)
			{
				UE_LOG(LogTemp, Warning, TEXT("AbilitySystemComponent is null."));
				return;
			}

			// Create a gameplay event payload
			FGameplayEventData EventData;
			EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.Movement"));

			// Create TargetData to hold FVector
			FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	    
			// Populate TargetData with a fake hit result for our input (hacky I know)
			FHitResult HitResult;
			HitResult.Location = FVector(Input.X, Input.Y, 0.0f); // Set the FVector here
			TargetData->HitResult = HitResult;

			// Add TargetData to the GameplayEventData
			EventData.TargetData = FGameplayAbilityTargetDataHandle(TargetData);

			// Trigger the event
			AbilitySystemComponent->HandleGameplayEvent(EventData.EventTag, &EventData);
	}
}

void ACharacterBase::InputActionJump_Implementation(EInputTypes InputType, bool Input)
{
	switch (InputType)
	{
		default: return;
	case EInputTypes::Started:
		if (AbilitySystemComponent)
		{
			if (!GetCharacterMovement()->IsFalling())
			{
				// Ground jump
				// Define optional event data
				FGameplayEventData Payload;
			
				// Trigger jump ability event
				AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Ability.Jump")), &Payload);
			}
			else if (!AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Ability.WallRun"))))
			{
				// Air jump
				// Define optional event data
				FGameplayEventData Payload;
			
				// Trigger air jump ability events
				// Trigger jump ability event
				AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Ability.AirJump")), &Payload);
			} else if (AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Ability.WallRun"))))
			{
				// Wall jump
				// Define optional event data
				FGameplayEventData Payload;
				
				AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Ability.WallJump")), &Payload);
			}
		}
	}
}

void ACharacterBase::InputActionDash_Implementation(const EInputTypes InputType, const bool Input)
{
	switch (InputType)
	{
		case EInputTypes::Started:
			if (!GetCharacterMovement()->IsFalling())
			{
				// Ground dash
				Execute_CharacterMovementGroundDash(this);
			}
			else
			{
				// Air dash
				Execute_CharacterMovementAirDash(this);
			}
	}
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
		AddNativeCharacterAbilities();
		AddInitialCharacterAbilities();

		// Add initial effects to ability system
		AddInitialCharacterGameplayEffects();
	}
}

void ACharacterBase::AddInitialCharacterAttributeSets()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AddSet<UHealthAttributeSet>();
		AbilitySystemComponent->AddSet<UAirActionAttributeSet>();
		AbilitySystemComponent->AddSet<UDashAttributeSet>();
		AbilitySystemComponent->AddSet<UCMCAttributeSet>();
	}
}

// Give native character abilities
void ACharacterBase::AddNativeCharacterAbilities()
{
	if (NativeAbilities.Num() > 0)
	{
		for (TSubclassOf<UNativeGameplayAbility> Ability : NativeAbilities)
		{
			if (Ability)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
			}
		}
	}
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
			// Valid gameplay effect
			if (GameplayEffect)
			{
				UE_LOG(LogTemp, Warning, TEXT("Adding initial gameplay effect: %s"), *GameplayEffect->GetName());
				// Create an outgoing spec for the Gameplay Effect
				FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect,1.f, AbilitySystemComponent->MakeEffectContext());
			
				// Apply the effect to the Ability System Component
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			}
		}
	}
}

// Make the character ground jump
void ACharacterBase::CharacterMovementJump_Implementation(FVector ForceDirection, float Strength, bool bSetZVelocityToZero)
{
	if (bSetZVelocityToZero)
	{
		FVector CurrentVelocity = GetCharacterMovement()->Velocity;
		GetCharacterMovement()->Velocity = FVector(CurrentVelocity.X, CurrentVelocity.Y, 0.0f);
	}
	GetCharacterMovement()->AddImpulse(ForceDirection * Strength, true);
}

// Air jump
void ACharacterBase::CharacterMovementAirJump_Implementation()
{
	
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
