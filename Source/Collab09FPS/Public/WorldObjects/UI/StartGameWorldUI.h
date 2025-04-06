// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldUIObjectBase.h"
#include "StartGameWorldUI.generated.h"

UCLASS()
class COLLAB09FPS_API AStartGameWorldUI : public AWorldUIObjectBase
{
public:
	// Sets default values for this actor's properties
	AStartGameWorldUI();

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	TSoftObjectPtr<UWorld> WorldToTransitionTo;

private:
	GENERATED_BODY()
};
