// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindRandomPatrol.h"
#include "Dog.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindRandomPatrol::UBTTask_FindRandomPatrol()
{
    NodeName = TEXT("Find Random Patrol");
}

EBTNodeResult::Type UBTTask_FindRandomPatrol::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    APawn *Pawn = OwnerComp.GetAIOwner()->GetPawn();

    if (Pawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    UNavigationSystemV1 *NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
    if (NavSystem == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    FNavLocation PatrolLocation;
    if (!NavSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), PatrolRadius, PatrolLocation))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Pawn->GetActorLocation());
        return EBTNodeResult::Failed;
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PatrolLocation.Location);
    return EBTNodeResult::Succeeded;
}
