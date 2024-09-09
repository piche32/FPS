// Fill out your copyright notice in the Description page of Project Settings.

#include "DisplayInfoUI.h"
#include "Components/TextBlock.h"

void UDisplayInfoUI::SetName(FText Value)
{
    if (Name)
    {
        if (Value.IsEmpty())
        {
            Name->SetVisibility(ESlateVisibility::Hidden);
        }
        else
        {
            Name->SetText(Value);
            Name->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void UDisplayInfoUI::SetAction(FText Value)
{
    if (Action)
    {
        if (Value.IsEmpty())
        {
            Name->SetVisibility(ESlateVisibility::Hidden);
        }
        else
        {
            Action->SetText(Value);
            Name->SetVisibility(ESlateVisibility::Visible);
        }
    }
}
