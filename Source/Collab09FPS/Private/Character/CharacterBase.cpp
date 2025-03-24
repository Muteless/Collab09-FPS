// Fill out your copyright notice in the Description page of Project Settings.

#include "Collab09FPS/Public/Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/AttributeSets/StaminaAttributeSet.h"

#pragma region Initialization

// Constructor
ACharacterBase::ACharacterBase() :
WeaponSocketName("WeaponSocket")
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

	WeaponLocation = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponLocation"));
	WeaponLocation->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
}

// AbilitySystemComponent interface, return ability system component
UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Get character movement component
UCharacterMovementComponent* ACharacterBase::GetActorCharacterMovementComponent_Implementation()
{
	return GetCharacterMovement();
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
		BindHealthAttributeSet();
		AbilitySystemComponent->AddSet<UAirActionAttributeSet>();
		AbilitySystemComponent->AddSet<UDashAttributeSet>();
		AbilitySystemComponent->AddSet<UCMCAttributeSet>();
		AbilitySystemComponent->AddSet<UMetaEffectsAttributeSet>();
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
				// Create an outgoing spec for the Gameplay Effect
				FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect,1.f, AbilitySystemComponent->MakeEffectContext());
			
				// Apply the effect to the Ability System Component
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			}
		}
	}
}

void ACharacterBase::BindHealthAttributeSet()
{
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	(HealthAttributeSet->GetCurrentHealthAttribute()).AddUObject
	(this, &ACharacterBase::OnHealthChanged);
}

void ACharacterBase::BindAirActionAttributeSet()
{
	
}

void ACharacterBase::BindCMCAttributeSet()
{
	
}

void ACharacterBase::BindDashAttributeSet()
{
	
}

void ACharacterBase::BindMetaEffectsAttributeSet()
{
	
}

#pragma endregion Initialization

#pragma region CMCAttributeSetChanges

void ACharacterBase::SetCMCMaxWalkSpeed_Implementation(float MaxWalkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

void ACharacterBase::SetCMCMaxAcceleration_Implementation(float MaxAcceleration)
{
	GetCharacterMovement()->MaxAcceleration = MaxAcceleration;
}

void ACharacterBase::SetCMCGravityScale_Implementation(float GravityScale)
{
	GetCharacterMovement()->GravityScale = GravityScale;
}

void ACharacterBase::SetCMCMaxWallRunSpeed_Implementation(float MaxWallRunSpeed)
{
	GetCharacterMovement()->MaxCustomMovementSpeed = MaxWallRunSpeed;
}

void ACharacterBase::SetCMCPushOffWallHorizontalSpeed_Implementation(float PushOffWallHorizontalSpeed)
{
	UCharacterMovementComponentBase* MovementComponentBase = Cast<UCharacterMovementComponentBase>
		(GetCharacterMovement());

	if (MovementComponentBase)
	{
		MovementComponentBase->EndWallRunOutImpulseStrength = PushOffWallHorizontalSpeed;
	}
}

void ACharacterBase::SetCMCPushOffWallVerticalSpeed_Implementation(float PushOffWallVerticalSpeed)
{
	UCharacterMovementComponentBase* MovementComponentBase = Cast<UCharacterMovementComponentBase>
		(GetCharacterMovement());

	if (MovementComponentBase)
	{
		MovementComponentBase->EndWallRunUpImpulseStrength = PushOffWallVerticalSpeed;
	}
}

void ACharacterBase::SetCMCGroundFriction_Implementation(float GroundFriction)
{
	GetCharacterMovement()->GroundFriction = GroundFriction;
}

void ACharacterBase::SetCMCBrakingFriction_Implementation(float BrakingFriction)
{
	GetCharacterMovement()->BrakingFriction = BrakingFriction;
}

void ACharacterBase::SetCMCSlidingSpeed_Implementation(float SlidingSpeed)
{
	UCharacterMovementComponentBase* MovementComponentBase = Cast<UCharacterMovementComponentBase>
		(GetCharacterMovement());

	if (MovementComponentBase)
	{
		MovementComponentBase->SlideSpeed = SlidingSpeed;
	}
}

#pragma region AttributeChangeDelegates

void ACharacterBase::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Health Changed"));
	if (Data.NewValue <= 0)
	{
		Death();
	}
}

void ACharacterBase::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	
}

void ACharacterBase::OnAirActionsChanged(const FOnAttributeChangeData& Data)
{
	
}

#pragma endregion AttributeChangeDelegates

#pragma endregion CMCAttributeSetChanges

#pragma region Input

void ACharacterBase::InputActionMove_Implementation(const EInputTypes InputType, const FVector2D Input)
{
	switch (InputType)
	{
		default: return;
		case EInputTypes::Triggered:
			if (!AbilitySystemComponent)
			{
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

/** TODO: refactor this as it is a slightly hard coded implementation of wall jumping, air jumping and ground jumping.
/ * Now, we as a team do not appear to want to change the types of jumps the player can do
	(or this list would expand quite rapidly) so I have come to this solution
	Grounded? Ground Jump
	IsNotWallRunnning && IsNotGrounded? Air Jump
	IsWallRunning? WallRun Jump*/
void ACharacterBase::InputActionJump_Implementation(EInputTypes InputType, bool Input)
{
	switch (InputType)
	{
		default: return;
	case EInputTypes::Started:
		if (AbilitySystemComponent)
		{
			if (!GetCharacterMovement()->IsFalling() &&
				!AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Effect.Movement.WallRunning"))))
			{
				// Ground jump payload
				// Define optional event data
				FGameplayEventData Payload;
				
				// Trigger jump ability event
				AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Ability.Jump")), &Payload);
			}
			else if (!AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Effect.Movement.WallRunning"))))
			{
				// Air jump
				// Define optional event data
				FGameplayEventData Payload;
				
				// Trigger air jump ability event
				AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Ability.AirJump")), &Payload);
			}
			if (AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Effect.Movement.WallRunning"))))
			{
				// Wall jump
				// Define optional event data
				FGameplayEventData Payload;
				
				// Trigger wall jump ability event
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
		case EInputTypes::Triggered:
			break;
		case EInputTypes::Ongoing:
			break;
		case EInputTypes::Cancelled:
			break;
		case EInputTypes::Completed:
			break;
	}
}

void ACharacterBase::InputActionSlide_Implementation(const EInputTypes InputType, const bool Input)
{
	switch (InputType)
	{
		case EInputTypes::Started:
			{
				if (!GetCharacterMovement()->IsFalling())
				{
					// Start sliding
					if (AbilitySystemComponent)
					{
						// slide payload
						FGameplayEventData Payload;
					
						// start slide ability event
						AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Ability.StartSlide")), &Payload);
						break;
					}
				}
			}
		
		case EInputTypes::Completed:
			{
				// Stop sliding
				if (AbilitySystemComponent)
				{
					// slide payload
					FGameplayEventData Payload;

					// stop sliding ability event
					AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Ability.StopSlide")), &Payload);
					break;
				}
			}
		case EInputTypes::Triggered:
			break;
		case EInputTypes::Ongoing:
			break;
		case EInputTypes::Cancelled:
			break;
	}
}

FVector ACharacterBase::GetMovementInput_Implementation()
{
	return GetLastMovementInputVector();
}

#pragma endregion Input

#pragma region Actions
void ACharacterBase::CharacterMovementMove_Implementation(FVector MoveInput)
{
	AddMovementInput(GetActorRightVector(), MoveInput.X, false);
	AddMovementInput(GetActorForwardVector(), MoveInput.Y, false);
}

void ACharacterBase::SpawnWeapon()
{
	// Check to see if weapon class is valid
	if (WeaponClass)
	{
		FTransform SpawnTransform;
		
		// Use weapon location as spawn location
		if (WeaponLocation)
		{
			SpawnTransform = WeaponLocation->GetComponentTransform();
		}
		else
		{
			SpawnTransform = FTransform(FRotator::ZeroRotator, GetActorLocation());
		}

		// Spawn weapon
		WeaponInstance = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, SpawnTransform);
		
		if (WeaponInstance)
		{
			// Set owner
			WeaponInstance->SetOwner(this);
			
			// Attach the weapon to the weapon location OR socket if available
			if (WeaponLocation)
			{
				WeaponInstance->AttachToComponent(WeaponLocation, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			}
			else if (USkeletalMeshComponent* CharacterMesh = GetMesh())
			{
				WeaponInstance->AttachToComponent(CharacterMesh,
					FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn weapon of class %s"),
				*WeaponClass->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponClass is not set in %s"),
			*GetName());
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

#pragma region WallRun

// TODO: refactor this into an ability? it is disgusting to look at //dan
void ACharacterBase::OnWallCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	UCharacterMovementComponentBase* MovementComponent = Cast<UCharacterMovementComponentBase>
		(GetCharacterMovement());
	
	// Movement component pointer is valid
	if (MovementComponent)
	{
		if (OtherActor && OtherActor != this)
		{
			if (MovementComponent->CanWallRun() && AbilitySystemComponent)
			{
				FHitResult HitResult;
				if (MovementComponent->IsWallDetected(HitResult))
				{
					MovementComponent->CurrentWallRunDirection = MovementComponent->GetWallRunDirection(HitResult);
					if (MovementComponent->InputDirectionWithinBounds())
					{
						// Create a gameplay event payload
						FGameplayEventData EventData;
						EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.WallRun"));
				
						AbilitySystemComponent->HandleGameplayEvent(EventData.EventTag, &EventData);
					}
				}
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

void ACharacterBase::CharacterMovementWallJump_Implementation(FVector Direction, float Strength)
{
	UCharacterMovementComponentBase* MovementComponent = Cast<UCharacterMovementComponentBase>
		(GetCharacterMovement());
	
	MovementComponent->bExitWallRun = true;
}

void ACharacterBase::CharacterMovementEndWallRun_Implementation()
{
	if (AbilitySystemComponent)
	{
		// Create a gameplay event payload
		FGameplayEventData EventData;
		EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Ability.WallRunEnd"));
		
		AbilitySystemComponent->HandleGameplayEvent(EventData.EventTag, &EventData);
	}
}

#pragma endregion WallRun

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

void ACharacterBase::CharacterMovementStartSliding_Implementation()
{
	UCharacterMovementComponentBase* MovementComponent = Cast<UCharacterMovementComponentBase>
		(GetCharacterMovement());
	
	MovementComponent->StartSliding();
}

void ACharacterBase::CharacterMovementStopSliding_Implementation()
{
	UCharacterMovementComponentBase* MovementComponent = Cast<UCharacterMovementComponentBase>
		(GetCharacterMovement());
	
	MovementComponent->StopSliding();
}

void ACharacterBase::Death()
{
	
}

#pragma endregion Actions

#pragma region GAS

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

#pragma endregion GAS
