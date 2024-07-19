// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDUI.generated.h"

class UInventoryUI;
class UTextBlock;
UCLASS()
class FPS_API UHUDUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryUI *InventoryUI;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidget *CrosshairUI;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock *InfoText;

	UPROPERTY(EditDefaultsOnly, Category = "Info/InfoText")
	float InfoTextVisibleTime = 5.0f;

private:

	FTimerHandle InfoTextVisibleTimer;

public:
	void RefreshInventoryWidget();
	void OpenInventoryUI();
	void CloseInventoryUI();
	bool GetIsInventoryVisible();
	void SetCrosshairVisible(bool Value);
	void SetInfoText(FText Value);
	void CloseInfoText();
	void Hide();
};
