// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"



#include "AirActionAttributeSet.generated.h"

// Attribute accessors
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UAirActionAttributeSet : public UAttributeSet
{
public:
	UAirActionAttributeSet();
	
	//*//
	// Max AirActions Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Actions | ")
	FGameplayAttributeData MaxAirActions;
	
	// Max AirAction Attribute Accessor
	ATTRIBUTE_ACCESSORS(UAirActionAttributeSet, MaxAirActions)

	// Current AirActions Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Actions | ")
	FGameplayAttributeData CurrentAirActions;
	
	// Current AirAction Attribute Accessor
	ATTRIBUTE_ACCESSORS(UAirActionAttributeSet, CurrentAirActions)

protected:
private:
	GENERATED_BODY()
};
