// Fill out your copyright notice in the Description page of Project Settings.

#include "CCTVAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

void ACCTVAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    SetFocus(PlayerPawn);

    PerceptionComponent = FindComponentByClass<UAIPerceptionComponent>();
    if (PerceptionComponent)
    {
        PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ACCTVAIController::SetHasLineOfSight);
    }
}

void ACCTVAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
    }
}

void ACCTVAIController::SetHasLineOfSight(AActor *Actor, FAIStimulus Stimulus)
{
    APawn *CastPawn = Cast<APawn>(Actor);
    if (CastPawn && CastPawn->IsPlayerControlled() && Stimulus.WasSuccessfullySensed())
    {
        Blackboard->SetValueAsBool(TEXT("HasLineOfSight"), true);
    }
    else
    {
        Blackboard->SetValueAsBool(TEXT("HasLineOfSight"), false);
        Blackboard->SetValueAsBool(TEXT("CanAttack"), false);
    }
}
