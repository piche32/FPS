// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"
#include "InventoryManagerComponent.h"
#include "Blueprint/UserWidget.h"
#include "HUDUI.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

AShooterPlayerController::AShooterPlayerController()
{
    InventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>(TEXT("Inventory"));
}

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUD = Cast<UHUDUI>(CreateWidget(this, HUDClass));
    if (HUD)
    {
        HUD->AddToViewport();
    }
}

void AShooterPlayerController::PickupItem(class AItemBase *Item)
{
    if (!InventoryManager)
    {
        return;
    }

    if (!HUD)
    {
        return;
    }
    InventoryManager->AddItem(Item);
    HUD->RefreshInventoryWidget();
}

void AShooterPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent)
    {
        if (UEnhancedInputComponent *Input = Cast<UEnhancedInputComponent>(InputComponent))
        {
            Input->BindAction(PickupAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::Pickup);
            Input->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::ToggleInventory);
        }
    }
}

void AShooterPlayerController::Pickup(const FInputActionValue &InputActionValue)
{
    PickupDelegate.ExecuteIfBound(this);
}

void AShooterPlayerController::ToggleInventory(const FInputActionValue &InputActionValue)
{
    if (!HUD)
    {
        return;
    }
    if (IsInventoryDelay)
    {
        return;
    }

    IsInventoryDelay = true;
    if (HUD->GetIsInventoryVisible())
    {
        CloseInventory();
    }
    else
    {
        OpenInventory();
    }

    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AShooterPlayerController::FinishTogglingInventory, InventoryDelayTime, false);
}

void AShooterPlayerController::OpenInventory()
{
    HUD->OpenInventoryUI();
    SetShowMouseCursor(true);
}

void AShooterPlayerController::CloseInventory()
{
    HUD->CloseInventoryUI();
    SetShowMouseCursor(false);
}

void AShooterPlayerController::FinishTogglingInventory()
{
    IsInventoryDelay = false;
}