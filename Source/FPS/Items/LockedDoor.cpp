// Fill out your copyright notice in the Description page of Project Settings.

#include "LockedDoor.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "../UI/DisplayInfoUI.h"
#include "../Shooter/ShooterPlayerController.h"
#include "../Components/InventoryManagerComponent.h"
#include "ItemBase.h"
#include "InteractiveDoor.h"

ALockedDoor::ALockedDoor()
{
    PrimaryActorTick.bCanEverTick = true;

    Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
    Widget->SetupAttachment(RootComponent);
}

void ALockedDoor::BeginPlay()
{
    Super::BeginPlay();

    InitializeWidget();
    InitializeCollision();
}

void ALockedDoor::OnOpen(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (!IsLocked)
    {
        Super::OnOpen(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    }
}

void ALockedDoor::OnClose(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    if (!IsLocked)
    {
        Super::OnClose(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
    }
}

void ALockedDoor::CollisionEnter(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    APawn *OtherPawn = Cast<APawn>(OtherActor);
    if (!OtherPawn || !OtherPawn->IsPlayerControlled())
    {
        return;
    }

    IsInRange = true;
    if (IsLocked)
    {
        Widget->SetVisibility(true);
    }
}

void ALockedDoor::CollisionExit(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    APawn *OtherPawn = Cast<APawn>(OtherActor);
    if (!OtherPawn || !OtherPawn->IsPlayerControlled())
    {
        return;
    }

    IsInRange = false;
    if (IsLocked)
    {
        Widget->SetVisibility(false);
    }
}

void ALockedDoor::Interact(APlayerController *Controller)
{
    if (!IsLocked)
    {
        return;
    }

    Unlock(Controller);
}

void ALockedDoor::Unlock(APlayerController *Controller)
{
    if (AShooterPlayerController *ShooterPlayerController = Cast<AShooterPlayerController>(Controller))
    {
        if (AItemBase *Key = ShooterPlayerController->GetInventoryManager()->GetItem(FText::FromString("Key")))
        {
            IsLocked = false;
            ShooterPlayerController->UseItem(Key);
            Widget->SetVisibility(false);
            AInteractiveDoor::OnOpen(ShooterPlayerController->GetPawn());
        }
        else
        {
            ShooterPlayerController->SetInfoText(LockedMessage);
        }
    }
}

void ALockedDoor::InitializeWidget()
{
    if (UDisplayInfoUIClass && Widget)
    {
        Widget->SetWidgetSpace(EWidgetSpace::Screen);
        Widget->SetWidgetClass(UDisplayInfoUIClass);
        Widget->InitWidget();
        Widget->SetVisibility(false);
    }

    if (UDisplayInfoUI *DisplayInfoUI = Cast<UDisplayInfoUI>(Widget->GetWidget()))
    {
        DisplayInfoUI->SetAction(ActionText);
    }
}

void ALockedDoor::InitializeCollision()
{

    if (Collision)
    {
        Collision->OnComponentBeginOverlap.AddDynamic(this, &ALockedDoor::CollisionEnter);
        Collision->OnComponentEndOverlap.AddDynamic(this, &ALockedDoor::CollisionExit);
    }
}
