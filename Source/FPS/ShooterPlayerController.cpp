// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"
#include "InventoryManagerComponent.h"

AShooterPlayerController::AShooterPlayerController()
{
    InventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>(TEXT("Inventory"));
}
