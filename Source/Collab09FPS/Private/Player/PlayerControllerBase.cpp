// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerControllerBase.h"
#include "GameFramework/SaveGame.h"
#include "Interfaces/GameInstanceInterface.h"
#include "Interfaces/LoadInterface.h"

void APlayerControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn->Implements<ULoadInterface>())
	{
		// Get save game
		USaveGame* SaveGame = IGameInstanceInterface::Execute_GetSaveGameData(GetGameInstance());
		ILoadInterface::Execute_LoadData(InPawn, SaveGame);
	}
}
