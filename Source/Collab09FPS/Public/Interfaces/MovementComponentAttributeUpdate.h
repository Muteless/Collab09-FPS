// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MovementComponentAttributeUpdate.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMovementComponentAttributeUpdate : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief Interface defining methods for updating specific attributes in the Character Movement Component (CMC).
 *
 * This interface provides a set of functionality for configuring and modifying various movement-related
 * properties used in a Character Movement Component. These properties include walking speed, wall running
 * speed, gravity scale, and others. Methods in this interface are intended to be implemented as Blueprint
 * native events to allow customization in both C++ and Unreal Engine Blueprint.
 */
class COLLAB09FPS_API IMovementComponentAttributeUpdate
{
public:
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "CMCAttributeSet")
	void SetCMCMaxWalkSpeed(float MaxWalkSpeed);
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "CMCAttributeSet")
	void SetCMCMaxWallRunSpeed(float MaxWallRunSpeed);
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "CMCAttributeSet")
	void SetCMCMaxAcceleration(float MaxAcceleration);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "CMCAttributeSet")
	void SetCMCGravityScale(float GravityScale);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "CMCAttributeSet")
	void SetCMCGroundFriction(float GroundFriction);
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "CMCAttributeSet")
	void SetCMCBrakingFriction(float BrakingForce);
	
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "CMCAttributeSet")
	void SetCMCPushOffWallHorizontalSpeed(float PushOffWallHorizontalSpeed);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "CMCAttributeSet")
	void SetCMCPushOffWallVerticalSpeed(float PushOffWallVerticalSpeed);

	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable,
		Category = "CMCAttributeSet")
	void SetCMCSlidingSpeed(float SlidingSpeed);

private:
	GENERATED_BODY()
};
