// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"

#include "GameplayEffect.h"
#include "Hitbox.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COLLAB09FPS_API UHitbox : public UBoxComponent
{
public:
	UHitbox();
	
	UPROPERTY()
	TMap<TSubclassOf<UGameplayEffect>, float> OnHitGameplayEffects;

private:
	GENERATED_BODY()
};
