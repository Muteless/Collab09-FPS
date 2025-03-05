// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"



#include "CharacterAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class COLLAB09FPS_API UCharacterAttributeSet : public UAttributeSet
{
public:
	// Health Attribute
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Health | ",
		ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	UFUNCTION()
	virtual void OnRep_Health();
	
private:
	GENERATED_BODY()
};
