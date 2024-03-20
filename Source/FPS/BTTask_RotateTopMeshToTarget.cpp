// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_RotateTopMeshToTarget.h"
#include "CCTV.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_RotateTopMeshToTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (ACCTV *CCTV = Cast<ACCTV>(OwnerComp.GetAIOwner()->GetPawn()))
    {
        CCTV->RotateToTarget(OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PlayerLocation")));
    }
    else
    {
        return EBTNodeResult::Failed;
    }
    return EBTNodeResult::Succeeded;
}
