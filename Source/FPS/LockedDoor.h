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

private:
	bool IsLocked = true;
	bool IsInRange = false;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UDisplayInfoUI> UDisplayInfoUIClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent *Widget;

	UPROPERTY(EditAnywhere, Category = "Info")
	FText ActionText = FText::FromString(TEXT("Press E"));

protected:
	virtual void BeginPlay() override;

private:
	void InitializeWidget();
	void InitializeCollision();

	virtual void OnOpen(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;

	virtual void OnClose(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	void CollisionEnter(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void CollisionExit(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

	virtual void Interact(APlayerController *Controller) override;
};
