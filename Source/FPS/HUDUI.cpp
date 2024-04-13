// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDUI.h"
#include "InventoryUI.h"
#include "ItemBase.h"
#include "ItemMenuUI.h"
#include "Components/Button.h"

void UHUDUI::RefreshInventoryWidget(const TArray<AItemBase *> &InventoryList)
{
    ActivateInventory = true;
    Inventory->Refresh(InventoryList);
}

void UHUDUI::OpenInventoryUI()
{
    Inventory->SetVisible(true);
}

void UHUDUI::CloseInventoryUI()
{
    Inventory->SetVisible(false);
    ItemMenu->SetVisible(false);
    ClickedItemIndex = -1;
}

bool UHUDUI::GetIsInventoryVisible()
{
    return Inventory->IsVisible();
}

void UHUDUI::OnClickInventorySlot(const int Index, FText ActionText)
{
    ActivateInventory = false;
    ClickedItemIndex = Index;
    ItemMenu->SetVisible(true);
    ItemMenu->SetActionText(ActionText);
}
