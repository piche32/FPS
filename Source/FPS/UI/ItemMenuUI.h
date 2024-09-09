// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopUpUI.h"
#include "InventoryUI.h"
#include "ItemMenuUI.generated.h"

class UButton;

UCLASS()
class FPS_API UItemMenuUI : public UUserWidget, public IPopUpUI
{
	GENERATED_BODY()

private:
	friend UInventoryUI;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton *ActionButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton *DropButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton *CancelButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock *ActionText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock *DetailText;

public:
	void SetVisible(bool Visible);
	void SetActionText(FText Value);
	void SetDetailText(FText Value);
	virtual void Close() override;
};
