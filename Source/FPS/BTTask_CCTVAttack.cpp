// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_CCTVAttack.h"
#include "CCTV.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_CCTVAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ACCTV *CCTV = Cast<ACCTV>(OwnerComp.GetAIOwner()->GetPawn());
    if (CCTV == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    CCTV->Attack(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    return EBTNodeResult::Succeeded;
}
