// Fill out your copyright notice in the Description page of Project Settings.

#include "TeleportableLockedDoor.h"
#include "Components/WidgetComponent.h"
#include "ShooterPlayerController.h"
#include "ItemBase.h"

void ATeleportableLockedDoor::Interact(APlayerController *Controller)
{
    if (!IsLocked)
    {
        Teleport(Controller);
        return;
    }

    Unlock(Controller);
    if (!IsLocked)
    {
        Teleport(Controller);
    }
}

void ATeleportableLockedDoor::OnOpen(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
}

void ATeleportableLockedDoor::OnClose(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
}

void ATeleportableLockedDoor::CollisionEnter(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    APawn *OtherPawn = Cast<APawn>(OtherActor);
    if (!OtherPawn || !OtherPawn->IsPlayerControlled())
    {
        return;
    }

    IsInRange = true;
    Widget->SetVisibility(true);
}

void ATeleportableLockedDoor::CollisionExit(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    APawn *OtherPawn = Cast<APawn>(OtherActor);
    if (!OtherPawn || !OtherPawn->IsPlayerControlled())
    {
        return;
    }

    Widget->SetVisibility(false);
}

void ATeleportableLockedDoor::Teleport(APlayerController *Controller)
{
    if (!Controller->GetPawn())
        return;

    FHitResult HitResult;
    Teleport(Controller->GetPawn());
}

void ATeleportableLockedDoor::Teleport(APawn *Target)
{
    if (!Target)
    {
        return;
    }
    FHitResult HitResult;
    Target->K2_SetActorTransform(TeleportTransform * GetActorTransform(), false, HitResult, true);
}
