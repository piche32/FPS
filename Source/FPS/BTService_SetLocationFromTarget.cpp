// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_SetLocationFromTarget.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_SetLocationFromTarget::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent *Blackboard = OwnerComp.GetBlackboardComponent();

    if (Blackboard == nullptr)
        return;

    AActor *Actor = Cast<AActor>(Blackboard->GetValueAsObject(TargetObject.SelectedKeyName));
    if (Actor)
    {
        Blackboard->SetValueAsVector(LocationVector.SelectedKeyName, Actor->GetActorLocation());
    }
}
