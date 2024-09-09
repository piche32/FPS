// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    SetFocus(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    PerceptionComponent = FindComponentByClass<UAIPerceptionComponent>();
    if (PerceptionComponent)
    {
        PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AShooterAIController::SetHasLineOfSight);
    }
}

void AShooterAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
    }

    Blackboard->SetValueAsVector(TEXT("OriginalPosition"), InPawn->GetActorLocation());
}

void AShooterAIController::SetHasLineOfSight(AActor *Actor, FAIStimulus Stimulus)
{
    APawn *CastPawn = Cast<APawn>(Actor);
    if (CastPawn != nullptr && CastPawn->IsPlayerControlled() && Stimulus.WasSuccessfullySensed())
    {
        GetWorldTimerManager().ClearTimer(SetHasLineOfSightTimer);
        Blackboard->SetValueAsBool(TEXT("HasLineOfSight"), true);
        Blackboard->SetValueAsObject(TEXT("Target"), Actor);
    }
    else
    {
        GetWorldTimerManager().SetTimer(
            SetHasLineOfSightTimer,
            this,
            &AShooterAIController::ClearHasLineOfSight,
            SetHasLineOfSightTime,
            false);
    }
}

void AShooterAIController::ClearHasLineOfSight()
{
    Blackboard->SetValueAsBool(TEXT("HasLineOfSight"), false);
    Blackboard->ClearValue(TEXT("Target"));
}
