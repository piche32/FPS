// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_UpdateWalkSpeed.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UBTTask_UpdateWalkSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_UpdateWalkSpeed();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
	float Speed = 500.f;
};
