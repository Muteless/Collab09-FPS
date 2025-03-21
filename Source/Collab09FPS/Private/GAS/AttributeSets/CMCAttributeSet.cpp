// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSets/CMCAttributeSet.h"
#include "Character/CharacterBase.h"

UCMCAttributeSet::UCMCAttributeSet()
{
	
}

void UCMCAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetMaxWalkSpeedAttribute())
	{
		Execute_SetCMCMaxWalkSpeed(GetOwningActor(), NewValue);
	}

	if (Attribute == GetMaxWallRunSpeedAttribute())
	{
		Execute_SetCMCMaxWallRunSpeed(GetOwningActor(), NewValue);
	}

	if (Attribute == GetMaxAccelerationAttribute())
	{
		Execute_SetCMCMaxAcceleration(GetOwningActor(), NewValue);
	}
	
	if (Attribute == GetGravityScaleAttribute())
	{
		Execute_SetCMCGravityScale(GetOwningActor(), NewValue);
	}

	if (Attribute == GetPushOffWallHorizontalImpulseStrengthAttribute())
	{
		Execute_SetCMCPushOffWallHorizontalSpeed(GetOwningActor(), NewValue);
	}

	if (Attribute == GetPushOffWallVerticalImpulseStrengthAttribute())
	{
		Execute_SetCMCPushOffWallVerticalSpeed(GetOwningActor(), NewValue);
	}
	
	Super::PreAttributeChange(Attribute, NewValue);
}

