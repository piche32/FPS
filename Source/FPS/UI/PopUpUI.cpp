// Fill out your copyright notice in the Description page of Project Settings.

#include "PopUpUI.h"

// Add default functionality here for any IPopUpUI functions that are not pure virtual.

void IPopUpUI::Close()
{
    UE_LOG(LogTemp, Warning, TEXT("Close"));
}

void IPopUpUI::Open()
{
    UE_LOG(LogTemp, Warning, TEXT("Open"));
}
