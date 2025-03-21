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
 * 
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
private:
	GENERATED_BODY()
};
