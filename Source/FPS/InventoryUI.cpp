// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryUI.h"
#include "InventorySlotUI.h"
#include "ItemBase.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/Button.h"
#include "InventoryManagerComponent.h"
#include "ShooterPlayerController.h"

void UInventoryUI::NativeConstruct()
{
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

void UInventoryUI::SetVisible(bool Visible)
{
    if (Visible)
    {
        SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        SetVisibility(ESlateVisibility::Hidden);
    }
}

void UInventoryUI::Refresh(const TArray<AItemBase *> &InventoryList)
{
    for (int i = 0; i < Slots.Num(); i++)
    {
        if (i < InventoryList.Num())
        {
            Slots[i]->Index = i;
            Slots[i]->ActionText = InventoryList[i]->GetActionText();
            Slots[i]->SetImage(InventoryList[i]->GetThumbnail());
            Slots[i]->Button->SetIsEnabled(true);
            Slots[i]->Button->OnClicked.AddDynamic(Slots[i], &UInventorySlotUI::OnClick);
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
