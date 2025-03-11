// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AIUtilities/BaseNavLinkProxy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/CharacterBase.h"
#include "DrawDebugHelpers.h"


// Sets default values
ABaseNavLinkProxy::ABaseNavLinkProxy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnSmartLinkReached.AddDynamic(this, &ABaseNavLinkProxy::OnNavLinkReached);
	UE_LOG(LogTemp,Log,TEXT("HELLO?"));
}

#include "DrawDebugHelpers.h"

void ABaseNavLinkProxy::OnNavLinkReached(AActor* MovingActor, const FVector& DestinationPoint)
{
    UE_LOG(LogTemp, Log, TEXT("OnNavLinkReached called for: %s"), *MovingActor->GetName());

    FVector StartLocation = MovingActor->GetActorLocation();
    FVector LaunchVelocity;
    
    FVector e = DestinationPoint;
    e.Z += 300; // I should probably make this a variable with a gizmo so designers can see what is going on a lil better (Later me problem)

    // Debug Sphere for Start Location
    DrawDebugSphere(GetWorld(), StartLocation, 50.0f, 12, FColor::Green, false, 5.0f);
    UE_LOG(LogTemp, Log, TEXT("Start Location: %s"), *StartLocation.ToString());

    // Debug Sphere for Target Location
    DrawDebugSphere(GetWorld(), e, 50.0f, 12, FColor::Blue, false, 5.0f);
    UE_LOG(LogTemp, Log, TEXT("Target Location (Adjusted): %s"), *e.ToString());

    // Debug Line Between Start and Target
    DrawDebugLine(GetWorld(), StartLocation, e, FColor::Cyan, false, 5.0f, 0, 2.0f);

    bool bSuccess = UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), LaunchVelocity, StartLocation, e);

    if (bSuccess)
    {
        UE_LOG(LogTemp, Log, TEXT("Launch Velocity Calculated: %s"), *LaunchVelocity.ToString());

        // Debug Line for the launch direction
        DrawDebugLine(GetWorld(), StartLocation, StartLocation + LaunchVelocity * 0.1f, FColor::Red, false, 5.0f, 0, 2.0f);

        #pragma region ACharacter
        ACharacter* Character = Cast<ACharacter>(MovingActor);
        if (Character)
        {
            Character->LaunchCharacter(LaunchVelocity, true, true);
            UE_LOG(LogTemp, Log, TEXT("%s successfully launched!"), *Character->GetName());
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
        
        // Debug Sphere to mark failure at start location
        DrawDebugSphere(GetWorld(), StartLocation, 60.0f, 12, FColor::Red, false, 5.0f);
    }
}



// Called every frame
void ABaseNavLinkProxy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

