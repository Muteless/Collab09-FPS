// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBase.generated.h"

UCLASS()
class COLLAB09FPS_API ABulletBase : public AActor
{

public:
	// Sets default values for this actor's properties
	ABulletBase();

	// Amount of ammo consumed on shot
	UPROPERTY(EditAnywhere)
	float AmmoConsumedOnShot;
	
protected:
	
private:
	GENERATED_BODY()
};
