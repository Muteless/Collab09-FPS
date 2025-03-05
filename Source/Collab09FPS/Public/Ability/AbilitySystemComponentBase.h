// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemComponentBase.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COLLAB09FPS_API UAbilitySystemComponentBase : public UAbilitySystemComponent
{
public:
	// Sets default values for this component's properties
	UAbilitySystemComponentBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
private:
	GENERATED_BODY()
};
