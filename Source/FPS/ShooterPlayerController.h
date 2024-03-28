// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

class UInventoryManagerComponent;

UCLASS()
class FPS_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShooterPlayerController();

private:
	UPROPERTY(VisibleAnywhere)
	UInventoryManagerComponent *InventoryManager;
};
