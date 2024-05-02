// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDUI.h"
#include "InventoryUI.h"
#include "Components/TextBlock.h"

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

void UHUDUI::SetInfoText(FText Value)
{
    InfoText->SetText(Value);
    InfoText->SetVisibility(ESlateVisibility::Visible);
    GetWorld()->GetTimerManager().SetTimer(
        InfoTextVisibleTimer,
        this,
        &UHUDUI::CloseInfoText,
        InfoTextVisibleTime, false);
}

void UHUDUI::CloseInfoText()
{
    InfoText->SetVisibility(ESlateVisibility::Hidden);
}
