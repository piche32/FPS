// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DogAIController.generated.h"

UCLASS()
class FPS_API ADogAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn *InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree *AIBehavior;

	UFUNCTION()
	void SetHasLineOfSightAndEnemyActor(AActor *Actor, FAIStimulus Stimulus);

	FTimerHandle SetHasLineOfSightTimer;

	UPROPERTY(EditDefaultsOnly)
	float SetHasLineOfSightTime = 4.0f;

	void ClearHasLineOfSightAndEnemyActor();
};
