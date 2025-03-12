// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"


#include "Interfaces/CharacterHUD.h"
#include "Widgets/SUserWidget.h"


#include "HUDBase.generated.h"


/**
 * @class AHUDBase
 * @brief AHUDBase is a base class for managing and rendering the Heads-Up Display (HUD) in the game.
 *
 * This class serves as the foundation for implementing custom HUD functionality
 * in the project. It inherits from the AHUD class provided by the Unreal Engine framework.
 */
UCLASS(Abstract)
class COLLAB09FPS_API AHUDBase :
public AHUD,
public ICharacterHUD
{
public:
	virtual void CreateHUD_Implementation(const ACharacterBase* Character) override;
protected:
private:
	GENERATED_BODY()
};
