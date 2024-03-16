// Fill out your copyright notice in the Description page of Project Settings.

#include "CCTVAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CCTV.h"

void ACCTVAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    SetFocus(PlayerPawn);
}

void ACCTVAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
    }

    CCTV = Cast<ACCTV>(InPawn);
}

void ACCTVAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CheckPlayerLocation();
}

void ACCTVAIController::CheckPlayerLocation()
{
    bool CanSearchPlayer = false;
    if (CCTV)
    {
        FVector Start = CCTV->GetViewPointLocation();
        FVector End = CCTV->GetViewPointForward() * SightRadius + Start;

        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(GetOwner());

        FHitResult HitResult;
        bool bHit = GetWorld()->SweepSingleByChannel(
            HitResult,
            Start,
            End,
            FQuat::Identity,
            ECC_GameTraceChannel2, // CCTV Trace Channel
            FCollisionShape::MakeSphere(TraceSphereRadius),
            CollisionParams);

        if (bHit)
        {
            //     DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, TraceSphereRadius, 12, FColor::Green, false, 5.f);
            //     DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.f);

            CCTV->UpdateLaserEnd(HitResult.ImpactPoint);
            if (APawn *HitPawn = Cast<APawn>(HitResult.GetActor()))
            {
                if (HitPawn->IsPlayerControlled())
                {
                    CanSearchPlayer = true;
                    Blackboard->SetValueAsBool(TEXT("CanAttack"), true);
                    Blackboard->SetValueAsVector(TEXT("PlayerLocation"), HitPawn->GetActorLocation());

                    if (SearchPlayerTimer.IsValid())
                    {
                        GetWorldTimerManager().ClearTimer(SearchPlayerTimer);
                    }
                }
            }
        }
        if (!CanSearchPlayer)
        {
            SetSearchPlayerTimer();
        }
    }
}
void ACCTVAIController::SetSearchPlayerTimer()
{
    if (SearchPlayerTimer.IsValid())
        return;

    GetWorldTimerManager().SetTimer(SearchPlayerTimer,
                                    this,
                                    &ACCTVAIController::ClearPlayerLocationAndCanAttack,
                                    SearchPlayerTime);
}

void ACCTVAIController::ClearPlayerLocationAndCanAttack()
{
    Blackboard->SetValueAsBool(TEXT("CanAttack"), false);
    Blackboard->ClearValue(TEXT("PlayerLocation"));
}