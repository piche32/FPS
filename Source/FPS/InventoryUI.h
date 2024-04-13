// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

class AItemBase;
class UInventorySlotUI;
UCLASS()
class FPS_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()

private:
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UInventorySlotUI *Slot1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UInventorySlotUI *Slot2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UInventorySlotUI *Slot3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UInventorySlotUI *Slot4;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UInventorySlotUI *Slot5;

	TArray<UInventorySlotUI *> Slots;
	virtual void NativeConstruct() override;

public:
	void SetVisible(bool Visible);
	void Refresh(const TArray<AItemBase *> &InventoryList);
};
