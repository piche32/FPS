// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySlotUI.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterPlayerController.h"
#include "HUDUI.h"

void UInventorySlotUI::SetImage(UTexture2D *Texture)
{
    if (ItemImage)
    {
        ItemImage->SetBrushFromTexture(Texture);
    }
}

void UInventorySlotUI::NativeConstruct()
{
    AShooterPlayerController *PlayerController =
        Cast<AShooterPlayerController>(
            UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (PlayerController)
    {
        HUD = PlayerController->GetHUD();
    }
}

void UInventorySlotUI::OnClick()
{
    if (OnSlotClicked.IsBound())
    {
        OnSlotClicked.Execute(Index, ActionText);
    }
}
