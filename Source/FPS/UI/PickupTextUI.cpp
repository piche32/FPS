// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupTextUI.h"
#include "Components/TextBlock.h"

void UPickupTextUI::SetText(FText Value)
{
    if (PickupText)
    {
        PickupText->SetText(Value);
    }
}
