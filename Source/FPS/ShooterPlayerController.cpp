// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"
#include "InventoryManagerComponent.h"
#include "Blueprint/UserWidget.h"

AShooterPlayerController::AShooterPlayerController()
{
    InventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>(TEXT("Inventory"));
}

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UUserWidget *HUD = CreateWidget(this, HUDClass);
    if (HUD)
    {
        HUD->AddToViewport();
    }
}
