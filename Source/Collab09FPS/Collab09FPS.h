// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Collab09FPS.generated.h"


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

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Attributes")
	float MaxHealth;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Attributes")
	float CurrentHealth;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Attributes")
	float MaxStamina;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Attributes")
	float CurrentStamina;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Attributes")
	float MaxAirActions;
};