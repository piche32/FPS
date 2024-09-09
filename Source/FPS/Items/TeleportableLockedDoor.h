// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LockedDoor.h"
#include "TeleportableLockedDoor.generated.h"

/**
 *
 */
UCLASS()
class FPS_API ATeleportableLockedDoor : public ALockedDoor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Info", meta = (MakeEditWidget = true))
	FTransform TeleportTransform;

protected:
	virtual void Interact(APlayerController *Controller) override;
	virtual void OnOpen(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;
	virtual void OnClose(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex) override;
	virtual void CollisionEnter(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	virtual void CollisionExit(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

private:
	void Teleport(APlayerController *Controller);
	void Teleport(APawn *Target);
};
