// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "HealthAttributeSet.generated.h"

// Attribute accessors
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * @class UHealthAttributeSet
 * @brief Attribute Set class that manages health attributes (Current and Max Health).
 *
 * This class is derived from UAttributeSet and is part of the Attribute Set system in Unreal Engine.
 * It includes functionality to replicate health-related attributes and clamps the current health
 * to ensure it stays within the valid range (0 to MaxHealth).
 */

UCLASS()
class COLLAB09FPS_API UHealthAttributeSet : public UAttributeSet
{
public:
	// Constructor
	UHealthAttributeSet();
	
	//*//
	// Max Health Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Health | ")
	FGameplayAttributeData MaxHealth;
	
	// Max Health Attribute Accessor
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxHealth)

	//*//
	// Current Health Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Health | ")
	FGameplayAttributeData CurrentHealth;

	// Current Health Attribute Accessor
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, CurrentHealth)

	//*//
	// Meta Damage Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Health | ")
	FGameplayAttributeData MetaDamage;
	
	// Meta Damage Attribute Accessor
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MetaDamage)

	// Meta Heal Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Health | ")
	FGameplayAttributeData MetaHeal;

	// Meta Heal Attribute Accessor
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MetaHeal)

protected:
	void virtual PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	void virtual PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;
private:
	GENERATED_BODY()
};
