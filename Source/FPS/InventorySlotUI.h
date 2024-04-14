// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.h"
#include "InventorySlotUI.generated.h"

UCLASS()
class FPS_API UInventorySlotUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetImage(UTexture2D *Texture);
	void DeleteClickFunction();
	int GetIndex()
	{
		return Index;
	}

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton *Button;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage *ItemImage;

	virtual void NativeConstruct() override;

private:
	int Index = -1;
	FText ActionText;
	class UHUDUI *HUD;

	UFUNCTION()
	void OnClick();

	DECLARE_DELEGATE_TwoParams(FOnSlotClicked, const int, FText);
	FOnSlotClicked OnSlotClicked;
	friend UInventoryUI;
};
