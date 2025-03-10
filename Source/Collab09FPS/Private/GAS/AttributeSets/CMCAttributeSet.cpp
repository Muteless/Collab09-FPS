// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/CMCAttributeSet.h"

UCMCAttributeSet::UCMCAttributeSet()
{
	// CMC
	GravityScale.SetBaseValue(2.8f);
	MaxAcceleration.SetBaseValue(3048.0f);
	BrakingFrictionFactor.SetBaseValue(1);
	BrakingFriction.SetBaseValue(6);
	CrouchedHalfHeight.SetBaseValue(40);
	bUseSeparateBrakingFactor.SetBaseValue(1);
	Mass.SetBaseValue(100);
	MaxStepHeight.SetBaseValue(45);
	WalkableFloorAngle.SetBaseValue(44.765083f);
	GroundFriction.SetBaseValue(8);
	MaxWalkSpeed.SetBaseValue(900);
	MaxWalkSpeedCrouched.SetBaseValue(300);
	MinAnalogWalkSpeed.SetBaseValue(0);
	BrakingDecelerationWalking.SetBaseValue(2048);
	JumpZVelocity.SetBaseValue(900);
	BrakingDecelarationFalling.SetBaseValue(0);
	AirControl.SetBaseValue(0.95f);
	AirControlBoostMultiplier.SetBaseValue(8);
	AirControlBoostVelocityThreshold.SetBaseValue(25);
	FallingLateralFriction.SetBaseValue(0);
	

	// Wall Running
	MaxWallRunningSpeed.SetBaseValue(1100);
	BrakingDecelerationWallRunning.SetBaseValue(0);
	WallRunSpeed.SetBaseValue(1100);
	MinWallRunSpeed.SetBaseValue(150);
	WallDetectionCapsuleRadius.SetBaseValue(54);
	WallDetectionCapsuleHeight.SetBaseValue(54);
	WallRunGravityX.SetBaseValue(0);
	WallRunGravityY.SetBaseValue(0);
	WallRunGravityZ.SetBaseValue(0);
	PushOffWallHorizontalImpulseStrength.SetBaseValue(900);
	PushOffWallVerticalImpulseStrength.SetBaseValue(900);
}

void UCMCAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
}
