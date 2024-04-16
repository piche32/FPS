// Fill out your copyright notice in the Description page of Project Settings.

#include "HealingItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Shooter.h"
#include "HealthComponent.h"

#define LOCTEXT_NAMESPACE "UINamespace"
void AHealingItemBase::Action()
{
    AShooter *Shooter = Cast<AShooter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (Shooter)
    {
        Shooter->GetHealthComponent()->AddHealth(HealingAmount);
    }
}

AHealingItemBase::AHealingItemBase()
{
    DetailText = FText::Format(NSLOCTEXT("UINamespace", "HealingItemDetailText", "사용 시, {0}만큼 회복!"), HealingAmount);
}

#undef LOCTEXT_NAMESPACE