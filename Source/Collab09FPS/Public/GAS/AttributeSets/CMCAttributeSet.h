// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "CMCAttributeSet.generated.h"

// Attribute accessors


/**
 * 
 */
UCLASS()
class COLLAB09FPS_API UCMCAttributeSet : public UAttributeSet
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

	//*// Wall Running
	// Max Wall Running Speed
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData MaxWallRunningSpeed;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, MaxWallRunningSpeed);
	
	// Wall Run Speed
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallRunSpeed;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, WallRunSpeed);

	// Min Speed For Wall Run
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData MinWallRunSpeed;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, MinWallRunSpeed);

	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData BrakingDecelerationWallRunning;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, BrakingDecelerationWallRunning);
	
	// Wall Detection Capsule Radius
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallDetectionCapsuleRadius;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, WallDetectionCapsuleRadius);

	// Wall Detection Capsule Height
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallDetectionCapsuleHeight;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, WallDetectionCapsuleHeight);

	// Wall Run Gravity Direction X
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallRunGravityX;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, WallRunGravityX);

	// Wall Run Gravity Direction Y
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallRunGravityY;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, WallRunGravityY);
	
	// Wall Run Gravity Direction Z
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallRunGravityZ;
	ATTRIBUTE_ACCESSORS(UCMCAttributeSet, WallRunGravityZ);

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
	
protected:
private:
	GENERATED_BODY()
};
