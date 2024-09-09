// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "HealingItemBase.generated.h"

/**
 *
 */
UCLASS()
class FPS_API AHealingItemBase : public AItemBase
{
	GENERATED_BODY()
public:
	AHealingItemBase();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float HealingAmount = 1.f;

	virtual void Action() override;
};
