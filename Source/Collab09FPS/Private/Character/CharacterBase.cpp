// Fill out your copyright notice in the Description page of Project Settings.


#include "Collab09FPS/Public/Character/CharacterBase.h"

#include "NavigationSystemTypes.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
	// Create AbilitySystemComponent
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponentBase>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
}

// AbilitySystemComponent interface, return ability system component
UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when character has been possessed
void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Initialize AbilitySystemComponent
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}