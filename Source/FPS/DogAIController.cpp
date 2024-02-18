// Fill out your copyright notice in the Description page of Project Settings.

#include "DogAIController.h"
#include "Kismet/GameplayStatics.h"

void ADogAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    SetFocus(PlayerPawn);
}
