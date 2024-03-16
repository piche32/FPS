// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_RotateTopMeshToTarget.h"
#include "CCTV.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_RotateTopMeshToTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController *AIController = OwnerComp.GetAIOwner();
    if (ACCTV *CCTV = Cast<ACCTV>(AIController->GetPawn()))
    {
        CCTV->RotateToTarget(AIController->GetBlackboardComponent()->GetValueAsVector(TEXT("PlayerLocation")));
    }
    else
    {
        return EBTNodeResult::Failed;
    }
    return EBTNodeResult::Succeeded;
}
