// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CCTVAIController.generated.h"

UCLASS()
class FPS_API ACCTVAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn *InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree *AIBehavior;

	UFUNCTION()
	void SetHasLineOfSight(AActor *Actor, FAIStimulus Stimulus);
};
