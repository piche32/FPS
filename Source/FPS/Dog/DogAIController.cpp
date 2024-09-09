// Fill out your copyright notice in the Description page of Project Settings.

#include "DogAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"

void ADogAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    SetFocus(PlayerPawn);

    Blackboard->SetValueAsVector(TEXT("OriginalPosition"), GetPawn()->GetActorLocation());

    PerceptionComponent = FindComponentByClass<UAIPerceptionComponent>();
    if (PerceptionComponent)
    {
        PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ADogAIController::SetHasLineOfSightAndEnemyActor);
    }
}

void ADogAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
    }
}

void ADogAIController::SetHasLineOfSightAndEnemyActor(AActor *Actor, FAIStimulus Stimulus)
{
    APawn *CastPawn = Cast<APawn>(Actor);
    if (CastPawn != nullptr && CastPawn->IsPlayerControlled() && Stimulus.WasSuccessfullySensed())
    {
        GetWorldTimerManager().ClearTimer(SetHasLineOfSightTimer);
        Blackboard->SetValueAsBool(TEXT("HasLineOfSight"), true);
        Blackboard->SetValueAsObject(TEXT("EnemyActor"), Actor);
    }
    else
    {
        GetWorldTimerManager().SetTimer(SetHasLineOfSightTimer, this, &ADogAIController::ClearHasLineOfSightAndEnemyActor, SetHasLineOfSightTime, false);
    }
}

void ADogAIController::ClearHasLineOfSightAndEnemyActor()
{
    Blackboard->SetValueAsBool(TEXT("HasLineOfSight"), false);
    Blackboard->SetValueAsObject(TEXT("EnemyActor"), nullptr);
}
