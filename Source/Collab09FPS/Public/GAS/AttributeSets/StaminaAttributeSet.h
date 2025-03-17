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
	UStaminaAttributeSet();

	//*//
	// Max Stamina Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Stamina | ")
	FGameplayAttributeData MaxStamina;
	
	// Max Stamina Attribute Accessor
	ATTRIBUTE_ACCESSORS(UStaminaAttributeSet, MaxStamina)

	//*//
	// Current Stamina Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Stamina | ")
	FGameplayAttributeData CurrentStamina;
	
	// Current Stamina Attribute Accessor
	ATTRIBUTE_ACCESSORS(UStaminaAttributeSet, CurrentStamina)

	//*//
	// Stamina Replenish Rate Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Stamina | ")
	FGameplayAttributeData StaminaReplenishRate;
	
	// Stamina Replenish Rate Attribute Accessor
	ATTRIBUTE_ACCESSORS(UStaminaAttributeSet, StaminaReplenishRate)

	//*//
	// Stamina Replenish Amount Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Stamina | ")
	FGameplayAttributeData StaminaReplenishAmount;
	
	// Stamina Replenish Amount Attribute Accessor
	ATTRIBUTE_ACCESSORS(UStaminaAttributeSet, StaminaReplenishAmount)
	
	//*//
	// Stamina Replenish Inhibit Duration Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Stamina | ")
	FGameplayAttributeData StaminaReplenishInhibitDuration;
	
	// Stamina Replenish Amount Attribute Accessor
	ATTRIBUTE_ACCESSORS(UStaminaAttributeSet, StaminaReplenishInhibitDuration)

protected:
	// Called before attribute changes
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
private:
	GENERATED_BODY()
};
