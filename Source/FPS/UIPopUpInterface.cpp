// Fill out your copyright notice in the Description page of Project Settings.

#include "UIPopUpInterface.h"

// Add default functionality here for any IUIPopUpInterface functions that are not pure virtual.

void IUIPopUpInterface::Close()
{
    UE_LOG(LogTemp, Warning, TEXT("Close"));
}

void IUIPopUpInterface::Open()
{
    UE_LOG(LogTemp, Warning, TEXT("Open"));
}
