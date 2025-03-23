// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Collab09FPS.generated.h"

#pragma region Enemy Spawner

UENUM(BlueprintType)
enum class EEnemyTypes : uint8
{
	DeepSeek UMETA(DisplayName = "DeepSeek"),
	Ranger UMETA(DisplayName = "Ranger"),
	HeavyRanger UMETA(DisplayName = "HeavyRanger"),
	Melee UMETA(DisplayName = "Melee"),
	HeavyMelee UMETA(DisplayName = "HeavyMelee")
};


UENUM(BlueprintType)
enum class ESpawnMode : uint8
{
	OnStart UMETA(DisplayName = "On Start"),
	OnEvent UMETA(DisplayName = "On Event"),
};

UENUM(BlueprintType)
enum class ERespawnMode : uint8
{
	Never UMETA(DisplayName = "Never"),
	OnTimer UMETA(DisplayName = "On Timer")
};

#pragma endregion Enemy Spawner

#pragma region World State

UENUM(BlueprintType)
enum class EWorldState : uint8
{
	WorldOne UMETA(DisplayName = "World One"),
	WorldTwo UMETA(DisplayName = "World Two"),
};

#pragma endregion World State

#pragma region Input

UENUM(BlueprintType)
enum class EInputTypes : uint8
{
	Triggered UMETA(DisplayName = "Triggered"),
	Started UMETA(DisplayName = "Started"),
	Ongoing UMETA(DisplayName = "Ongoing"),
	Cancelled UMETA(DisplayName = "Cancelled"),
	Completed UMETA(DisplayName = "Completed")
};


USTRUCT(BlueprintType)
struct FBoolInput
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputTypes InputType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Input;

	// Default constructor
	FBoolInput()
		: InputType(EInputTypes::Triggered)
		, Input(false)
	{}

	
	// Custom constructor
	FBoolInput(const EInputTypes InInputType, const bool InInput)
		: InputType(InInputType)
		, Input(InInput)
	{}

};

USTRUCT(BlueprintType)
struct FVector2DInput
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputTypes InputType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Input;

	// Default constructor
	FVector2DInput()
		: InputType(EInputTypes::Triggered)
		, Input(FVector2D::ZeroVector)
	{}

	
	// Custom constructor
	FVector2DInput(const EInputTypes InInputType, const FVector2D InInputs)
		: InputType(InInputType)
		, Input(InInputs)
	{}
};

#pragma endregion Input