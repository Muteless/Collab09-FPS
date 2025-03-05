// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"


#include "PlayerStateBase.generated.h"

/**
 * @class APlayerStateBase
 * @brief This class serves as the base implementation for player's state in the game.
 *
 * APlayerStateBase extends the APlayerState class and provides a foundation
 * for representing and managing player-specific state information in the game.
 *
 * It is intended to be extended for specialized functionalities or behaviors
 * related to the player's state during gameplay.
 */
UCLASS(Abstract)
class COLLAB09FPS_API APlayerStateBase : public APlayerState
{
	GENERATED_BODY()
};
