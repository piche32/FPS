// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDUI.h"
#include "InventoryUI.h"

void UHUDUI::RefreshInventoryWidget()
{
    InventoryUI->Refresh();
}

void UHUDUI::OpenInventoryUI()
{
    InventoryUI->Open();
}

void UHUDUI::CloseInventoryUI()
{
    InventoryUI->Close();
}

bool UHUDUI::GetIsInventoryVisible()
{
    return InventoryUI->GetIsInventoryVisible();
}

void UHUDUI::SetCrosshairVisible(bool Value)
{
    if (Value)
    {
        CrosshairUI->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        CrosshairUI->SetVisibility(ESlateVisibility::Hidden);
    }
}
