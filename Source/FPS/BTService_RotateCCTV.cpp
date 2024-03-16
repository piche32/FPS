// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_RotateCCTV.h"
#include "CCTV.h"
#include "AIController.h"

void UBTService_RotateCCTV::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ACCTV *CCTV = Cast<ACCTV>(OwnerComp.GetAIOwner()->GetPawn());
    if (CCTV)
    {
        CCTV->Rotate(DeltaSeconds);
    }
}
