// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_UpdateWalkSpeed.h"
#include "Dog.h"
#include "AIController.h"

UBTTask_UpdateWalkSpeed::UBTTask_UpdateWalkSpeed()
{
    NodeName = TEXT("Update Walk Speed");
}

EBTNodeResult::Type UBTTask_UpdateWalkSpeed::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ADog *Dog = Cast<ADog>(OwnerComp.GetAIOwner()->GetPawn());

    if (Dog == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Dog->UpdateWalkSpeed(Speed);

    return EBTNodeResult::Succeeded;
}
