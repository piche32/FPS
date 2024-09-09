// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveDoor.h"
#include "InteractInterface.h"
#include "LockedDoor.generated.h"

class UWidgetComponent;
class UDisplayInfoUI;

UCLASS()
class FPS_API ALockedDoor : public AInteractiveDoor, public IInteractInterface
{
	GENERATED_BODY()

public:
	ALockedDoor();

protected:
	UPROPERTY(EditAnywhere, Category = "Info")
	bool IsLocked = true;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent *Widget;

	bool IsInRange = false;

	UPROPERTY(EditAnywhere, Category = "UI")
	FText LockedMessage = FText::FromString(TEXT("이 문은 잠겨 있습니다."));

private:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UDisplayInfoUI> UDisplayInfoUIClass;

	UPROPERTY(EditAnywhere, Category = "Info")
	FText ActionText = FText::FromString(TEXT("F : 열기"));

protected:
	virtual void BeginPlay() override;

	virtual void OnOpen(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
	 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;
	virtual void OnClose(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
	 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	virtual void CollisionEnter(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
	 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
	virtual void CollisionExit(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
	 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

	virtual void Interact(APlayerController *Controller) override;
	void Unlock(APlayerController *Controller);

private:
	void InitializeWidget();
	void InitializeCollision();
};
