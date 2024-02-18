// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DogAIController.generated.h"

UCLASS()
class FPS_API ADogAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
};
