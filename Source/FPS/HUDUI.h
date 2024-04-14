// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDUI.generated.h"

class UInventoryUI;

UCLASS()
class FPS_API UHUDUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void RefreshInventoryWidget();
	void OpenInventoryUI();
	void CloseInventoryUI();
	bool GetIsInventoryVisible();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryUI *InventoryUI;
};
