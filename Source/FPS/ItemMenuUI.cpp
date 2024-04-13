// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemMenuUI.h"
#include "Components/TextBlock.h"

void UItemMenuUI::SetVisible(bool Visible)
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

void UItemMenuUI::SetActionText(FText Value)
{
    ActionText->SetText(Value);
}

void UItemMenuUI::Close()
{
    SetVisible(false);
}
