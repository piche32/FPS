// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"
#include "../Components/InventoryManagerComponent.h"
#include "Blueprint/UserWidget.h"
#include "../UI/HUDUI.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "../Items/ItemBase.h"
#include "Shooter.h"
#include "../Items/InteractInterface.h"

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

void AShooterPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent)
    {
        if (UEnhancedInputComponent *Input = Cast<UEnhancedInputComponent>(InputComponent))
        {
            Input->BindAction(PickupAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::Pickup);
            Input->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::ToggleInventory);
            Input->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::Interact);
        }
    }
}

void AShooterPlayerController::Pickup(const FInputActionValue &InputActionValue)
{
    if (!bIsMovable)
        return;
    PickupDelegate.Broadcast(this);
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
    SetFocusOnUI();
}

void AShooterPlayerController::CloseInventory()
{
    HUD->CloseInventoryUI();
    SetFocusOnGameplay();
}

void AShooterPlayerController::FinishTogglingInventory()
{
    IsInventoryDelay = false;
}

void AShooterPlayerController::SetFocusOnUI()
{
    bIsMovable = false;
    SetShowMouseCursor(true);
    SetInputMode(FInputModeGameAndUI());
    HUD->SetCrosshairVisible(false);
}

void AShooterPlayerController::SetFocusOnGameplay()
{
    bIsMovable = true;
    SetShowMouseCursor(false);
    SetInputMode(FInputModeGameOnly());
    HUD->SetCrosshairVisible(true);
}

void AShooterPlayerController::HideHUD()
{
    HUD->Hide();
}

void AShooterPlayerController::Interact()
{
    TArray<AActor *> OverlappingActors;
    GetPawn()->GetOverlappingActors(OverlappingActors);

    for (AActor *OverlappingActor : OverlappingActors)
    {
        IInteractInterface *InteractObject = Cast<IInteractInterface>(OverlappingActor);
        if (!InteractObject)
        {
            continue;
        }

        InteractObject->Interact(this);
    }
}

void AShooterPlayerController::PickupItem(AItemBase *Item)
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

void AShooterPlayerController::DropItem(const int ItemIndex)
{
    if (!InventoryManager)
    {
        return;
    }

    AItemBase *Item = InventoryManager->GetItem(ItemIndex);
    if (!Item)
        return;
    AShooter *Shooter = Cast<AShooter>(GetPawn());
    if (!Shooter)
        return;
    Item->Drop(Shooter->GetDropPosition());

    InventoryManager->RemoveItemByIndex(ItemIndex);
}

void AShooterPlayerController::UseItem(const int ItemIndex)
{
    if (!InventoryManager)
    {
        return;
    }
    AItemBase *Item = InventoryManager->GetItem(ItemIndex);
    if (!Item)
        return;
    Item->Action();
    if (Item->IsConsumable())
    {
        InventoryManager->RemoveItemByIndex(ItemIndex);
    }
}

void AShooterPlayerController::UseItem(class AItemBase *Item)
{
    if (!InventoryManager)
    {
        return;
    }
    if (!Item)
        return;
    Item->Action();
    if (Item->IsConsumable())
    {
        InventoryManager->RemoveItemByName(Item->GetName());
    }
}

void AShooterPlayerController::SetInfoText(FText Value)
{
    HUD->SetInfoText(Value);
}
