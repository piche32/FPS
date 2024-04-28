// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryUI.h"
#include "InventorySlotUI.h"
#include "ItemBase.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/Button.h"
#include "InventoryManagerComponent.h"
#include "ShooterPlayerController.h"
#include "Components/Widget.h"
#include "Kismet/GameplayStatics.h"
#include "ItemMenuUI.h"
#include "InventoryManagerComponent.h"

void UInventoryUI::NativeConstruct()
{
    AShooterPlayerController *PlayerController =
        Cast<AShooterPlayerController>(
            UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (PlayerController)
    {
        InventoryManager = PlayerController->GetInventoryManager();
    }
    Slots.Add(Slot1);
    Slots.Add(Slot2);
    Slots.Add(Slot3);
    Slots.Add(Slot4);
    Slots.Add(Slot5);

    for (int i = 0; i < Slots.Num(); i++)
    {
        Slots[i]->Button->SetIsEnabled(false);
    }

    InitializeItemMenu();
}

void UInventoryUI::InitializeItemMenu()
{
    if (!ItemMenu)
        return;
    if (ItemMenu->CancelButton)
    {
        ItemMenu->CancelButton->OnClicked.AddDynamic(this, &UInventoryUI::CloseItemMenu);
    }
    if (ItemMenu->DropButton)
    {
        ItemMenu->DropButton->OnClicked.AddDynamic(this, &UInventoryUI::OnClickDropButton);
    }
    if (ItemMenu->ActionButton)
    {
        ItemMenu->ActionButton->OnClicked.AddDynamic(this, &UInventoryUI::OnClickActionButton);
    }
}

void UInventoryUI::CloseItemMenu()
{
    ActivateInventory = true;
    ClickedItemIndex = -1;
    ItemMenu->Close();
}

void UInventoryUI::OnClickDropButton()
{
    AShooterPlayerController *PlayerController =
        Cast<AShooterPlayerController>(
            UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (!PlayerController)
        return;
    PlayerController->DropItem(ClickedItemIndex);
    Refresh();
    CloseItemMenu();
}

void UInventoryUI::OnClickActionButton()
{
    AShooterPlayerController *PlayerController =
        Cast<AShooterPlayerController>(
            UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (!PlayerController)
        return;
    PlayerController->UseItem(ClickedItemIndex);
    Refresh();
    CloseItemMenu();
}

bool UInventoryUI::GetIsInventoryVisible()
{
    return Inventory->IsVisible();
}

void UInventoryUI::SetVisible(UWidget *Widget, bool Visible)
{
    if (Visible)
    {
        Widget->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        Widget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UInventoryUI::Refresh()
{
    ActivateInventory = true;
    const TArray<AItemBase *> InventoryList = InventoryManager->GetInventoryList();
    for (int i = 0; i < Slots.Num(); i++)
    {
        if (i < InventoryList.Num())
        {
            Slots[i]->Index = i;
            Slots[i]->ActionText = InventoryList[i]->GetActionText();
            Slots[i]->SetImage(InventoryList[i]->GetThumbnail());
            Slots[i]->Button->SetIsEnabled(true);
            Slots[i]->OnSlotClicked.BindUObject(this, &UInventoryUI::OnClickInventorySlot);
        }
        else
        {
            Slots[i]->Index = -1;
            Slots[i]->ActionText = FText::FromString(TEXT(""));
            Slots[i]->SetImage(nullptr);
            Slots[i]->Button->SetIsEnabled(false);
        }
    }
}

void UInventoryUI::Open()
{
    SetVisible(Inventory, true);
    Refresh();
}

void UInventoryUI::Close()
{
    SetVisible(Inventory, false);
    SetVisible(ItemMenu, false);
    ClickedItemIndex = -1;
}

void UInventoryUI::OnClickInventorySlot(const int Index, FText ActionText)
{
    ActivateInventory = false;
    ClickedItemIndex = Index;
    SetVisible(ItemMenu, true);
    ItemMenu->SetActionText(ActionText);
    ItemMenu->SetDetailText(InventoryManager->GetItem(Index)->GetDetailText());
}
