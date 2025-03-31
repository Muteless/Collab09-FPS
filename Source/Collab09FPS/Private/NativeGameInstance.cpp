// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PersistentData/SaveGameData.h"

void UNativeGameInstance::Init()
{
	Super::Init();

	// load game
	SaveGame = IGameInstanceInterface::Execute_LoadGame(this);
}

#pragma region WorldState

int UNativeGameInstance::GetWorldIndex_Implementation()
{
	return WorldIndex;
}

ULevelDataAsset* UNativeGameInstance::GetLevelData_Implementation()
{
	return WorldData[WorldIndex];
}


#pragma endregion WorldState

#pragma region SaveGame

void UNativeGameInstance::SaveGame_Implementation()
{
	FAsyncSaveGameToSlotDelegate SaveCompleteDelegate;
	SaveCompleteDelegate.BindLambda([this](
		const FString& SlotName,
		int32 UserIndex,
		bool bSuccess
		)
	{
		if (bSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Game Success"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Game Failed"));
		}
	});

	UGameplayStatics::AsyncSaveGameToSlot(
		SaveGame,
		SaveSlot,
		SaveSlotIndex,
		SaveCompleteDelegate
		);
}

USaveGame* UNativeGameInstance::GetSaveGameData_Implementation()
{
	return SaveGame;
}

void UNativeGameInstance::SetSaveSlot_Implementation(FName SlotName)
{
	SaveSlot = SlotName.ToString();
}

FString UNativeGameInstance::GetSaveSlot_Implementation()
{
	return SaveSlot;
}

USaveGame* UNativeGameInstance::LoadGame_Implementation()
{
	// load save game from slot
	SaveGame = UGameplayStatics::LoadGameFromSlot(
		SaveSlot,
		SaveSlotIndex
		);

	// if save game does not exist, create it
	if (!SaveGame || !SaveGame->IsValidLowLevelFast())
	{
		SaveGame = UGameplayStatics::CreateSaveGameObject(TSubclassOf<USaveGameData>
			(USaveGameData::StaticClass()));

		// save game to slot
		IGameInstanceInterface::Execute_SaveGame(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Game is valid"));
	}
	
	return SaveGame;
}

#pragma endregion SaveGame

void UNativeGameInstance::Shutdown()
{
	Super::Shutdown();
}