// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Collab09FPS/Collab09FPS.h"

#include "Engine/DataAsset.h"
#include "LevelDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class COLLAB09FPS_API ULevelDataAsset : public UDataAsset
{
public:
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	TSoftObjectPtr<UWorld> PersistentWorld;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite)
	TMap<EWorldState, TSoftObjectPtr<UWorld>> WorldCollection;
	
protected:
private:
	GENERATED_BODY()
};
