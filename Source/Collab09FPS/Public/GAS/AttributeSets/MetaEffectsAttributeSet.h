﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "MetaEffectsAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UMetaEffectsAttributeSet : public UAttributeSet
{
public:
	#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Meta Effects | ")
	FGameplayAttributeData MetaKnockBack;

	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Meta Effects | ")
	FGameplayAttributeData MetaRootMotionImpulse;

	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Meta Effects | ")
	FGameplayAttributeData MetaRootMotionForce;
	
private:
	GENERATED_BODY()
};
