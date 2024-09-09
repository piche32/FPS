// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySlotUI.h"
#include "Components/Image.h"
#include "Components/Button.h"

void UInventorySlotUI::SetImage(UTexture2D *Texture)
{
    if (ItemImage)
    {
        ItemImage->SetBrushFromTexture(Texture);
    }
}

void UInventorySlotUI::NativeConstruct()
{
    if (!Button)
        return;
    Button->OnClicked.AddDynamic(this, &UInventorySlotUI::OnClick);
}

void UInventorySlotUI::OnClick()
{
    if (OnSlotClicked.IsBound())
    {
        OnSlotClicked.Execute(Index, ActionText);
    }
}
