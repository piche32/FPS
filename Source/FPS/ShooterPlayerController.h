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

protected:
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

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction *InteractAction;

	bool bIsMovable = true;

public:
	AShooterPlayerController();

protected:
	virtual void BeginPlay() override;

public:
	UHUDUI *GetHUD()
	{
		return HUD;
	}

	UFUNCTION(BlueprintPure)
	UInventoryManagerComponent *GetInventoryManager() const
	{
		return InventoryManager;
	}

	bool GetIsMovable() const
	{
		return bIsMovable;
	}

private:
	void Pickup(const FInputActionValue &InputActionValue);
	void ToggleInventory(const FInputActionValue &InputActionValue);
	void OpenInventory();
	void CloseInventory();

	bool IsInventoryDelay = false;

	void FinishTogglingInventory();

	void SetFocusOnUI();
	void SetFocusOnGameplay();

	void Interact();

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	float InventoryDelayTime = 0.5f;

	virtual void SetupInputComponent() override;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FPickupDelegate, AShooterPlayerController *);
	FPickupDelegate PickupDelegate;

	void PickupItem(class AItemBase *Item);
	void DropItem(const int ItemIndex);
	void UseItem(const int ItemIndex);
	void UseItem(class AItemBase *Item);

	void SetInfoText(FText Value);
};
