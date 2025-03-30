// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldObjects/UI/WorldUIObjectBase.h"


// Sets default values
AWorldUIObjectBase::AWorldUIObjectBase():
BoxComponent(nullptr)
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
}