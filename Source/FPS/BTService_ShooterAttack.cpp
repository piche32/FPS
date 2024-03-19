// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_ShooterAttack.h"
#include "Shooter.h"
#include "AIController.h"

void UBTService_ShooterAttack::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (AShooter *Shooter = Cast<AShooter>(OwnerComp.GetAIOwner()->GetPawn()))
    {
        Shooter->OnShoot();
    }
}
