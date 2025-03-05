// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"



#include "StaminaAttributeSet.generated.h"

// Attribute accessor macros
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * UStaminaAttributeSet is a subclass of UAttributeSet designed to manage
 * attributes related to stamina in the game, such as the maximum stamina
 * and current stamina for players or entities. It serves as a container
 * and handler for stamina-related attributes and associated replication logic.
 */

UCLASS()
class COLLAB09FPS_API UStaminaAttributeSet : public UAttributeSet
{
public:

	//*//
	// Max Stamina Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Health | ",
		ReplicatedUsing=OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	UFUNCTION()
	virtual void OnRep_MaxStamina();
	
	// Max Health Attribute Accessor
	ATTRIBUTE_ACCESSORS(UStaminaAttributeSet, MaxStamina)

	//*//
	// Current Stamina Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Health | ",
		ReplicatedUsing=OnRep_CurrentStamina)
	FGameplayAttributeData CurrentStamina;
	UFUNCTION()
	virtual void OnRep_CurrentStamina();
	
	// Max Health Attribute Accessor
	ATTRIBUTE_ACCESSORS(UStaminaAttributeSet, CurrentStamina)

protected:
	// Called before attribute changes
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// Get LifetimeReplicatedProps override
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	GENERATED_BODY()
};
