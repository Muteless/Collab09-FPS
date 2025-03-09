// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterMovementComponentBase.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COLLAB09FPS_API UCharacterMovementComponentBase : public UCharacterMovementComponent
{
public:
	// Sets default values for this component's properties
	UCharacterMovementComponentBase();
	enum ECustomMovementMode : uint8
	{
		MOVE_WallRunning = 0
	};

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	void PerformWallRun(float DeltaTime);
	bool IsWallDetected(FHitResult& WallHit) const;
	
	FVector GetWallRunDirection(const FHitResult& WallHit) const;
	
	UFUNCTION(BlueprintPure,
		Category = "WallRunning")
	bool CanWallRun() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Wall-run settings
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "WallRunning")
	float WallRunSpeed = 600.f;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "WallRunning")
	float MinimumWallRunEntrySpeed = 50.f;
	
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "WallRunning")
	float WallDetectionRange = 100.f;

	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category = "WallRunning")
	float WallRunGravityScale = 0.5f;

private:
	GENERATED_BODY()
};
