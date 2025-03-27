// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class COLLAB09FPS_API ALevelGameMode : public AGameModeBase
{
public:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
private:
	GENERATED_BODY()
};
