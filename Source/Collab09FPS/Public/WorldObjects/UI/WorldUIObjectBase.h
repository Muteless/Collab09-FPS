// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "WorldUIObjectBase.generated.h"

UCLASS()
class COLLAB09FPS_API AWorldUIObjectBase : public AActor
{
public:
	// Sets default values for this actor's properties
	AWorldUIObjectBase();

	UPROPERTY(EditAnywhere, Category = "Default")
	UBoxComponent* BoxComponent;

private:
	GENERATED_BODY()

};
