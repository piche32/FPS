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
            Slots[i]->Button->OnClicked.AddDynamic(Slots[i], &UInventorySlotUI::OnClick);
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

bool UInventoryUI::GetIsInventoryVisible()
{
    return Inventory->IsVisible();
}

void UInventoryUI::Open()
{
    SetVisible(Inventory, true);
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
}
