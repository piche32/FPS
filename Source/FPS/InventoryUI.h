// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

class AItemBase;
class UInventorySlotUI;
class UItemMenuUI;
class UWidget;
UCLASS()
{
	GENERATED_BODY()

private:
	class UInventoryManagerComponent *InventoryManager;
	int ClickedItemIndex = -1;
	bool ActivateInventory = true;

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

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UItemMenuUI *ItemMenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidget *Inventory;

protected:
	virtual void NativeConstruct() override;

public:
	bool GetActivateInventory()
	{
		return ActivateInventory;
	}
	bool GetIsInventoryVisible();
	void Open();
	void Close();
	void SetVisible(UWidget *Widget, bool Visible);

	void Refresh();

	void OnClickInventorySlot(const int Index, FText ActionText);
};
