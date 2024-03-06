// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DogAttack.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UBTTask_DogAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_DogAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
