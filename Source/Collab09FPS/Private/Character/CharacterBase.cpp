// Fill out your copyright notice in the Description page of Project Settings.


#include "Collab09FPS/Public/Character/CharacterBase.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
	
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}