// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemMenuUI.generated.h"

class UButton;

UCLASS()
class FPS_API UItemMenuUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton *ActionButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton *DropButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton *CancelButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock *ActionText;

public:
	void SetVisible(bool Visible);
	void SetActionText(FText Value);

private:
	void Close();
};
