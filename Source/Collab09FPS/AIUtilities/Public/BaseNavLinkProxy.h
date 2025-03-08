// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "BaseNavLinkProxy.generated.h"

UCLASS()
class COLLAB09FPS_API ABaseNavLinkProxy : public ANavLinkProxy
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseNavLinkProxy();

protected:
	UFUNCTION()
	virtual void OnNavLinkReached(AActor* MovingActor, const FVector& DestinationPoint);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
