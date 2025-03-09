// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AIUtilities/BaseNavLinkProxy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/CharacterBase.h"


// Sets default values
ABaseNavLinkProxy::ABaseNavLinkProxy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnSmartLinkReached.AddDynamic(this, &ABaseNavLinkProxy::OnNavLinkReached);
	UE_LOG(LogTemp,Log,TEXT("HELLO?"));
}

void ABaseNavLinkProxy::OnNavLinkReached(AActor* MovingActor, const FVector& DestinationPoint)
{
	UE_LOG(LogTemp, Log, TEXT("MF IS JUMPING OR FALLING"));

	FVector StartLocation = MovingActor->GetActorLocation();
	FVector LaunchVelocity;

	FVector e = DestinationPoint;
	e.Z += 250;
	
	bool bSuccess = UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), LaunchVelocity, StartLocation, e);

	if (bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("Launch Velocity: %s"), *LaunchVelocity.ToString());
		
		#pragma region ACharacter
		ACharacter* Character = Cast<ACharacter>(MovingActor);
		if (Character)
		{
			Character->LaunchCharacter(LaunchVelocity, true, true);
			UE_LOG(LogTemp, Log, TEXT("MF DID JUMPING OR FALLING"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to cast MovingActor to ACharacter!"));
		}
		#pragma endregion
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SuggestProjectileVelocity failed, no valid trajectory found!"));
	}
}


// Called every frame
void ABaseNavLinkProxy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

