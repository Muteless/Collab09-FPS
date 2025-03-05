// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Character/CharacterBase.h"

#include "PlayerControllerBase.generated.h"

/**
 * @class APlayerControllerBase
 * @brief A base class for managing player controllers.
 *
 * This class inherits from APlayerController and is intended to provide
 * foundational functionality for controlling player characters. It serves as the
 * base class for player-specific behavior and input handling within the game framework.
 *
 * The class is designed for extensibility and can be derived to implement custom
 * gameplay logic and input.
 */
UCLASS(Abstract)
class COLLAB09FPS_API APlayerControllerBase : public APlayerController
{
public:
	
private:
	GENERATED_BODY()
};
