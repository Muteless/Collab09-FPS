// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "CMCAttributeSet.generated.h"

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
class COLLAB09FPS_API UCMCAttributeSet : public UAttributeSet
{
	
public:
	// Constructor
	UCMCAttributeSet();
	
	//*// Base CMC
	// Gravity Scale
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData GravityScale;

	// Max Acceleration
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData MaxAcceleration;

	// Braking Friction Factor
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData BrakingFrictionFactor;

	// Braking Friction
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData BrakingFriction;

	// Crouched Half Height
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData CrouchedHalfHeight;

	// Use Separate Braking Factor?
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData bUseSeparateBrakingFactor;

	// Mass
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData Mass;

	// Max Step Height
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData MaxStepHeight;

	// Walkable Floor Angle
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WalkableFloorAngle;

	// Ground Friction
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData GroundFriction;
	
	// Max Walk Speed
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData MaxWalkSpeed;

	// Max Walk Speed Crouched
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData MaxWalkSpeedCrouched;

	// Min Analog Walk Speed
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData MinAnalogWalkSpeed;

	// Braking Deceleration Walking
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData BrakingDecelerationWalking;

	// Jump Z Velocity
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData JumpZVelocity;

	// Braking Deceleration Falling
    	UPROPERTY(BlueprintReadOnly,
    		Category="Attributes | CMC | ")
    	FGameplayAttributeData BrakingDecelarationFalling;

	// Air Control
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData AirControl;

	// Air Control Boost Multiplier
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData AirControlBoostMultiplier;

	// Air Control Boost Velocity Threshold
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData AirControlBoostVelocityThreshold;

	// Falling Lateral Friction
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData FallingLateralFriction;

	// Max Wall Running Speed
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData MaxWallRunningSpeed;

	// Braking Deceleration Flying
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData BrakingDecelerationWallRunning;

	//*// Wall Running
	// Wall Run Speed
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallRunSpeed;

	// Min Speed For Wall Run
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData MinWallRunSpeed;

	// Wall Detection Capsule Radius
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallDetectionCapsuleRadius;

	// Wall Detection Capsule Height
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallDetectionCapsuleHeight;

	// Wall Run Gravity Direction X
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallRunGravityX;

	// Wall Run Gravity Direction Y
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallRunGravityY;
	
	// Wall Run Gravity Direction Z
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData WallRunGravityZ;

	// Applied on the XY axis when a character stops wall running
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData PushOffWallHorizontalImpulseStrength;

	// Applied on the Z axis when a character stops wall running
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | CMC | ")
	FGameplayAttributeData PushOffWallVerticalImpulseStrength;
	
protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
private:
	GENERATED_BODY()
};
