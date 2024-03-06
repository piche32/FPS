// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_DogAttack.h"
#include "Dog.h"
#include "AIController.h"

UBTTask_DogAttack::UBTTask_DogAttack()
{
    NodeName = TEXT("Dog Attack");
}

EBTNodeResult::Type UBTTask_DogAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ADog *Dog = Cast<ADog>(OwnerComp.GetAIOwner()->GetPawn());

    if (Dog == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Dog->StartAttacked();
    return EBTNodeResult::Succeeded;
}
