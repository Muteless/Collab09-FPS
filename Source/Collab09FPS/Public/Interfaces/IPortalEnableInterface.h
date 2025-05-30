﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPortalEnableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UIPortalEnableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLAB09FPS_API IIPortalEnableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent,
		BlueprintCallable)
	void EnablePortal();
};
