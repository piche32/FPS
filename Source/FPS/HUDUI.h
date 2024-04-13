// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDUI.generated.h"

class UInventoryUI;
class AItemBase;
class UItemMenuUI;

UCLASS()
class FPS_API UHUDUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void RefreshInventoryWidget(const TArray<AItemBase *> &InventoryList);
	void OpenInventoryUI();
	void CloseInventoryUI();
	bool GetActivateInventory()
	{
		return ActivateInventory;
	}
	bool GetIsInventoryVisible();

	void OnClickInventorySlot(const int Index, FText ActionText);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryUI *Inventory;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UItemMenuUI *ItemMenu;

	virtual void NativeConstruct() override;

private:
	bool ActivateInventory = true;
	int ClickedItemIndex = -1;
};
