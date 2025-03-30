// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterBase.h"

#include "Collab09FPS/Collab09FPS.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/CharacterController.h"

// Constructor
APlayerCharacterBase::APlayerCharacterBase() :
WeaponSocketName("WeaponSocket")
{
	// CMC
	GetCharacterMovement()->SetActive(true);
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Create and configure a SpringArmComponent
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());  // Attach SpringArm to CapsuleComponent
	SpringArmComponent->TargetArmLength = 10.0f;						// Set the distance the camera will follow
	SpringArmComponent->bUsePawnControlRotation = true;					// Rotate arm based on controller movement
	SpringArmComponent->bDoCollisionTest = false;						// Don't want to collide with the arm
	SpringArmComponent->bEnableCameraLag = true;						// Enable camera lag
	SpringArmComponent->CameraLagSpeed = 5.0f;							// Set the camera lag speed

	// Create and configure the CameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);      // Attach the camera to the SpringArm
	CameraComponent->bUsePawnControlRotation = false;          // This disables direct control rotation, relying on spring arm

	// FOV
	FOVMinimum = 90;
	FOVMaximum = 110;
	MinFOVSpeedThreshold = 100.0f;
	MaxFOVSpeedThreshold = 1100.0f;
	FOVInterpSpeed = 5.0f;
	
	// Ensure the pawn itself doesn't rotate the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Attribute sets
	StaminaAttributeSet = CreateDefaultSubobject<UStaminaAttributeSet>(TEXT("Stamina Attribute Set"));
	
	PrimaryActorTick.bCanEverTick = true;

	// Wall capsule component
	WallCapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Wall Capsule Collision"));
	WallCapsuleCollision->SetupAttachment(GetCapsuleComponent());
	WallCapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WallCapsuleCollision->SetCollisionObjectType(ECC_EngineTraceChannel2);
	WallCapsuleCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	WallCapsuleCollision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	WallCapsuleCollision->SetGenerateOverlapEvents(true);
	
	WallCapsuleCollision->ShapeColor = FColor::Blue;
	WallCapsuleCollision->SetLineThickness(1);
	WallCapsuleCollision->SetCapsuleSize(GetCapsuleComponent()->GetScaledCapsuleRadius() + WallCapsuleDetectionOffsetRadius, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	// Weapon location
	WeaponLocation = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponLocation"));
	WeaponLocation->SetupAttachment(CameraComponent, NAME_None);
}

void APlayerCharacterBase::LoadData_Implementation(USaveGame* SaveGame)
{
	UPlayerSaveData* PlayerSaveData = ISaveGameInterface::Execute_GetPlayerSaveData(SaveGame);

	if (PlayerSaveData)
	{
		if (!WeaponInstance)
		{
			SpawnWeapon();
		}

		if (WeaponInstance)
		{
			if (PlayerSaveData->GunAssetData)
			{
				WeaponInstance->GunAssetData = PlayerSaveData->GunAssetData;
			}

			if (PlayerSaveData->MeleeAssetData)
			{
				WeaponInstance->MeleeAssetData = PlayerSaveData->MeleeAssetData;
			}
		}

		WeaponInstance->bGunMode = PlayerSaveData->bGunMode;
		WeaponInstance->Initialize();
	}
}

void APlayerCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Initialize wall capsule collision
	if (WallCapsuleCollision)
	{
		// Begin & end overlap events
		WallCapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacterBase::OnWallCapsuleBeginOverlap);
		WallCapsuleCollision->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacterBase::OnWallCapsuleEndOverlap);
	}
}

UPlayerSaveData* APlayerCharacterBase::MakePlayerSaveData()
{
	UPlayerSaveData* PlayerSaveData = NewObject<UPlayerSaveData>();

	if (WeaponInstance)
	{
		PlayerSaveData->bGunMode = WeaponInstance->bGunMode;
		PlayerSaveData->GunAssetData = WeaponInstance->GunAssetData;
		PlayerSaveData->MeleeAssetData = WeaponInstance->MeleeAssetData;
		return PlayerSaveData;
	}
	
	return nullptr;
}

void APlayerCharacterBase::AddInitialCharacterAttributeSets()
{
	Super::AddInitialCharacterAttributeSets();
	
	if (AbilitySystemComponent)
	{
		// Stamina
		AbilitySystemComponent->AddSet<UStaminaAttributeSet>();
	}
}

// Tick
void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update FOV based on speed
	UpdateFOVBasedOnSpeed(DeltaTime);
}

// Camera
void APlayerCharacterBase::InputActionLook_Implementation(EInputTypes InputType, FVector2D Input)
{
	AddControllerYawInput(bInvertedYaw ? Input.X : -Input.X);
	AddControllerPitchInput(bInvertedPitch ? Input.Y : -Input.Y);
}

void APlayerCharacterBase::InputActionSwitchDimensions_Implementation(const EInputTypes InputType, const bool Input)
{
	switch (InputType)
	{
	case EInputTypes::Triggered:
		break;
	case EInputTypes::Started:
			// Switch dimensions
			if (AbilitySystemComponent)
			{
				// slide payload
				FGameplayEventData Payload;
					
				// start slide ability event
				AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Ability.SwitchDimensions")), &Payload);
				break;
			}
	case EInputTypes::Ongoing:
		break;
	case EInputTypes::Cancelled:
		break;
	case EInputTypes::Completed:
		break;
	}
}

void APlayerCharacterBase::InputActionInteract_Implementation(const EInputTypes InputType, const bool Input)
{
	
}

void APlayerCharacterBase::SpawnWeapon()
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

			// Notify controller that we have spawned the weapon
			ICharacterController::Execute_WeaponSpawned(GetController(), WeaponInstance);
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

void APlayerCharacterBase::UpdateFOVBasedOnSpeed(float DeltaTime) const
{
	float CurrentSpeed = GetVelocity().Size();

	// Ensure the camera component is valid
	if (!CameraComponent) return;
	
	// Map speed to FOV
	float TargetFOV = FMath::Lerp(FOVMinimum,
		FOVMaximum,
		FMath::Clamp((CurrentSpeed - MinFOVSpeedThreshold) / (MaxFOVSpeedThreshold - MinFOVSpeedThreshold),
			0.0f,
			1.0f));

	float CurrentFOV = CameraComponent->FieldOfView;
	CameraComponent->FieldOfView = FMath::FInterpTo(CurrentFOV,
		TargetFOV,
		DeltaTime,
		FOVInterpSpeed);
}

#pragma region WallRun

// TODO: refactor this into an ability? it is disgusting to look at //dan
void APlayerCharacterBase::OnWallCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
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

void APlayerCharacterBase::OnWallCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		
	}
}

void APlayerCharacterBase::CharacterMovementWallRun_Implementation()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}

void APlayerCharacterBase::CharacterMovementWallJump_Implementation(FVector Direction, float Strength)
{
	UCharacterMovementComponentBase* MovementComponent = Cast<UCharacterMovementComponentBase>
		(GetCharacterMovement());
	
	MovementComponent->bExitWallRun = true;
}

void APlayerCharacterBase::CharacterMovementEndWallRun_Implementation()
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

#pragma region CMCAttributeSetChanges

void APlayerCharacterBase::SetCMCMaxWallRunSpeed_Implementation(float MaxWallRunSpeed)
{
	GetCharacterMovement()->MaxCustomMovementSpeed = MaxWallRunSpeed;
}

void APlayerCharacterBase::SetCMCPushOffWallHorizontalSpeed_Implementation(float PushOffWallHorizontalSpeed)
{
	UCharacterMovementComponentBase* MovementComponentBase = Cast<UCharacterMovementComponentBase>
		(GetCharacterMovement());

	if (MovementComponentBase)
	{
		MovementComponentBase->EndWallRunOutImpulseStrength = PushOffWallHorizontalSpeed;
	}
}

void APlayerCharacterBase::SetCMCPushOffWallVerticalSpeed_Implementation(float PushOffWallVerticalSpeed)
{
	UCharacterMovementComponentBase* MovementComponentBase = Cast<UCharacterMovementComponentBase>
		(GetCharacterMovement());

	if (MovementComponentBase)
	{
		MovementComponentBase->EndWallRunUpImpulseStrength = PushOffWallVerticalSpeed;
	}
}

#pragma endregion CMCAttributeSetChanges

//* Blueprint Helper functions *//
// Get current stamina attribute
float APlayerCharacterBase::GetCurrentStamina() const
{
	if (StaminaAttributeSet)
	{
		return StaminaAttributeSet->GetCurrentStamina();
	}
	return -1.0f;
}