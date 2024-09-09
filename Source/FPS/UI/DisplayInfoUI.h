// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DisplayInfoUI.generated.h"

/**
 *
 */

class UTextBlock;
UCLASS()
class FPS_API UDisplayInfoUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetName(FText Value);
	void SetAction(FText Value);
	;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock *Name;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock *Action;
};
