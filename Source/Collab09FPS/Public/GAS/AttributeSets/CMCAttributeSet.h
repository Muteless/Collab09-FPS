// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Interfaces/MovementComponentAttributeUpdate.h"


#include "CMCAttributeSet.generated.h"

// Attribute accessors


/**
 * Class for defining an attribute set related to Character Movement Component (CMC).
 */
UCLASS()
class COLLAB09FPS_API UCMCAttributeSet : public UAttributeSet,
public IMovementComponentAttributeUpdate
{
	
public:
	#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
	
	// Constructor
	UCMCAttributeSet();
	
	// Max Walk Speed
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData MaxWalkSpeed;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, MaxWalkSpeed);
	
	// Max Acceleration
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData MaxAcceleration;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, MaxAcceleration);

	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData GroundJumpZVelocity;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, GroundJumpZVelocity);

	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData AirJumpZVelocity;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, AirJumpZVelocity);

	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallJumpZVelocity;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, WallJumpZVelocity);

	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData GravityScale;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, GravityScale);

	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData GroundFriction;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, GroundFriction);

	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData BrakingFriction;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, BrakingFriction);

	//*// Wall Running
	// Wall Run Speed
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData MaxWallRunSpeed;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, MaxWallRunSpeed);

	// Applied on the XY axis when a character stops wall running
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData PushOffWallHorizontalImpulseStrength;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, PushOffWallHorizontalImpulseStrength);

	// Applied on the Z axis when a character stops wall running
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData PushOffWallVerticalImpulseStrength;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, PushOffWallVerticalImpulseStrength);

	// Crouching & Sliding
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData SlidingSpeed;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, SlidingSpeed);

protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute,
		float& NewValue) override;
private:
	GENERATED_BODY()
};
