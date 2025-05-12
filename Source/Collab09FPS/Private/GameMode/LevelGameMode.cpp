// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LevelGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "GameFramework/SaveGame.h"

#include "Interfaces/GameInstanceInterface.h"
#include "Interfaces/LoadInterface.h"
#include "Interfaces/SaveGameInterface.h"

#include "Kismet/GameplayStatics.h"

#include "WorldObjects/Checkpoint.h"

// todo: not this, ew, disgusting, evil, sick and twisted function
// to any of the art team, this is like triangulating your entire model and giving it to someone
AActor* ALevelGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	// Get save game
	USaveGame* SaveGame = IGameInstanceInterface::Execute_LoadGame(GetGameInstance());
	
	// Get checkpoint index from file
	int CheckpointIndex = ISaveGameInterface::Execute_GetCheckpointIndex(SaveGame);

	// get all the checkpoints in the level
	TArray<AActor*> Checkpoints;
	UGameplayStatics::GetAllActorsOfClass(this, ACheckpoint::StaticClass(), Checkpoints);

	// iterate and find checkpoint with matching save game checkpoint index
	for (AActor* Checkpoint : Checkpoints)
	{
		ACheckpoint* CheckpointActor = Cast<ACheckpoint>(Checkpoint);
		if (CheckpointActor->Id == CheckpointIndex)
		{
			Player->SetControlRotation(CheckpointActor->GetRootComponent()->GetComponentRotation());
			return CheckpointActor;
		}
	}

	// if we could not find valid checkpoint with id, default to player start
	TArray<AActor*> PlayerStarts;
	UE_LOG(LogTemp, Error, TEXT("FAILED TO FIND CHECKPOINT WITH ID %i"), CheckpointIndex)
	UE_LOG(LogTemp, Error, TEXT("ATTEMPTING TO FIND PLAYER STARTS"))
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);

	// iterate and return first player start
	for (AActor* PlayerStart : PlayerStarts)
	{
		APlayerStart* PlayerStartActor = Cast<APlayerStart>(PlayerStart);
		Player->SetControlRotation(PlayerStartActor->GetActorRotation());
		return PlayerStartActor;
	}

	UE_LOG(LogTemp, Error, TEXT("FAILED TO FIND PLAYER START"))
	UE_LOG(LogTemp, Error, TEXT("MAKING A PLAYER START AS A LAST RESORT"))
	AActor* PlayerStart = GetWorld()->SpawnActor<APlayerStart>();
	
	return PlayerStart;
}