// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"



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
		Category="Attributes | Health | ",
		ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	UFUNCTION()
	virtual void OnRep_MaxHealth();
	
	// Max Health Attribute Accessor
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxHealth)

	//*//
	// Current Health Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Health | ",
		ReplicatedUsing=OnRep_CurrentHealth)
	FGameplayAttributeData CurrentHealth;
	UFUNCTION()
	virtual void OnRep_CurrentHealth();

	// Current Health Attribute Accessor
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, CurrentHealth)

	//*//
	// Get LifetimeReplicatedProps override
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	// Called before attribute changes
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
private:
	GENERATED_BODY()
};
