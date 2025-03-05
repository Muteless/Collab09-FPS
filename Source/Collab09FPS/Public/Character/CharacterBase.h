// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemComponent.h"
#include "Ability/AbilitySystemComponentBase.h"
#include "GameplayAbilities/Public/AbilitySystemInterface.h"

#include "CharacterBase.generated.h"

UCLASS(Abstract)
class COLLAB09FPS_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
public:
	// Sets default values for this character's properties
	ACharacterBase();

	// Ability System Component
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	// Possessed by controller
	virtual void PossessedBy(AController* NewController) override;

private:
	GENERATED_BODY()

};
