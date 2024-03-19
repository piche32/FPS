// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SetLocationFromTarget.generated.h"

/**
 *
 */
struct FBlackboardKeySelector;

UCLASS()
class FPS_API UBTService_SetLocationFromTarget : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetObject;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector LocationVector;
};
