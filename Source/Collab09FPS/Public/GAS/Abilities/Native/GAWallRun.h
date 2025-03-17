// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayAbility.h"
#include "GAWallRun.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class COLLAB09FPS_API UGAWallRun : public UNativeGameplayAbility
{
public:
protected:
	// Activate wall run
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	bool CanWallRun(const FGameplayAbilityActorInfo* ActorInfo, FHitResult& HitResult);
	bool IsWallDetected(const FGameplayAbilityActorInfo* ActorInfo, FHitResult& HitResultt) const;
	void BeginWallRun(const FGameplayAbilityActorInfo* ActorInfo, FHitResult& HitResult);

	void PerformWallRun(const FGameplayAbilityActorInfo* ActorInfo, FHitResult& HitResult);
	
	// End wall run
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;

	void EndWallRun();

	// Upper wall detection capsule
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UpperWallDetectionCapsuleHeight = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UpperWallDetectionCapsuleRadius = 50;
	
	// Lower wall detection capsule
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LowerWallDetectionCapsuleHeight = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LowerWallDetectionCapsuleRadius = 50;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinimumWallFacingThreshold = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaximumWallFacingThreshold = 0.5;
	
private:
	GENERATED_BODY()
};
