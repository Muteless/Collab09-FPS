// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldObjects/Checkpoint.h"

#include "Interfaces/GameInstanceInterface.h"
#include "Player/PlayerCharacterBase.h"


// Sets default values
ACheckpoint::ACheckpoint()
{
	PlayerSpawnLocation = CreateDefaultSubobject<UBillboardComponent>(TEXT("PlayerSpawnLocation"));
	RootComponent = PlayerSpawnLocation;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCapsuleSize(34, 88);
	CapsuleComponent->SetupAttachment(PlayerSpawnLocation);
	
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(CapsuleComponent);
	ArrowComponent->ArrowColor = FColor::Green;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(100, 100, 100));
	BoxComponent->SetCollisionProfileName(TEXT("Checkpoint"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->ShapeColor = FColor::Green;
	BoxComponent->SetLineThickness(5);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACheckpoint::OnBoxEndOverlap);

	FAttachmentTransformRules TransformRules
		(EAttachmentRule::KeepWorld,
		EAttachmentRule::KeepWorld,
		EAttachmentRule::KeepRelative,
		false);
	
	BoxComponent->AttachToComponent(PlayerSpawnLocation, TransformRules, NAME_None);
	BoxComponent->SetWorldLocation(PlayerSpawnLocation->GetComponentLocation());
}

#pragma region BoxComponent

void ACheckpoint::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (APlayerCharacterBase* PlayerCharacter = Cast<APlayerCharacterBase>(OtherActor))
	{
		// Get save game from game instance
		USaveGame* SaveGame = IGameInstanceInterface::Execute_GetSaveGameData(GetGameInstance());
		ULevelDataAsset* LevelDataAsset = IGameInstanceInterface::Execute_GetLevelData(GetGameInstance());

		// if save game is valid then set data
		if (SaveGame)
		{
			// ignore checkpoint if id is less then save game id
			if (ISaveGameInterface::Execute_GetCheckpointIndex(SaveGame) > Id)
			{
				return;
			}
			
			ISaveGameInterface::Execute_SetCheckpointIndex(SaveGame, Id);
			ISaveGameInterface::Execute_SetPlayerSaveData(SaveGame, PlayerCharacter->MakePlayerSaveData());
			ISaveGameInterface::Execute_SetLevelDataAsset(SaveGame, LevelDataAsset);

			// set save game data
			IGameInstanceInterface::Execute_SaveGame(GetGameInstance());
		}
		else
		{
			// this will externally create a save game
			IGameInstanceInterface::Execute_LoadGame(GetGameInstance());

			// recursively call to save data again
			OnBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
		}
	}
}

void ACheckpoint::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
}

#pragma endregion BoxComponent