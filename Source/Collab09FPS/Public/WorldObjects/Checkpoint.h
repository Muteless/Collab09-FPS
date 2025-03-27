// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"

#include "Checkpoint.generated.h"

UCLASS()
class COLLAB09FPS_API ACheckpoint : public AActor
{
public:
	ACheckpoint();

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Default")
	int Id;
	
	UPROPERTY(EditAnywhere,
    		BlueprintReadWrite,
    		Category = "Components")
	UBillboardComponent* PlayerSpawnLocation;

protected:

#pragma region Components

	#pragma region BoxComponent
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "Components")
	UBoxComponent* BoxComponent;

	// Event handlers for overlap
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	#pragma endregion BoxComponent

	UPROPERTY()
	UArrowComponent* ArrowComponent;

	UPROPERTY()
	UCapsuleComponent* CapsuleComponent;

#pragma endregion Components
	
private:
	GENERATED_BODY()
};
