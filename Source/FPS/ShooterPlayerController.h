// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InventoryManagerComponent.h"
#include "ShooterPlayerController.generated.h"

class UHUDUI;
class UInputAction;
struct FInputActionValue;

UCLASS()
class FPS_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShooterPlayerController();

	void PickupItem(class AItemBase *Item);
	UHUDUI *GetHUD()
	{
		return HUD;
	}
	UInventoryManagerComponent *GetInventoryManager()
	{
		return InventoryManager;
	}

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UHUDUI> HUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UHUDUI *HUD;

private:
	UPROPERTY(VisibleAnywhere)
	UInventoryManagerComponent *InventoryManager;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction *PickupAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction *InventoryAction;

	void Pickup(const FInputActionValue &InputActionValue);
	void ToggleInventory(const FInputActionValue &InputActionValue);
	void OpenInventory();
	void CloseInventory();

	bool IsInventoryDelay = false;

	void FinishTogglingInventory();

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	float InventoryDelayTime = 0.5f;

	virtual void SetupInputComponent() override;

public:
	DECLARE_DELEGATE_OneParam(FPickupDelegate, AShooterPlayerController *);
	FPickupDelegate PickupDelegate;
};
