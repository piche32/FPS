// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickupTextUI.generated.h"

UCLASS()
class FPS_API UPickupTextUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetText(FText Value);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock *PickupText;
};
