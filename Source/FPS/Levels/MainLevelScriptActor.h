// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainLevelScriptActor.generated.h"

/**
 *
 */

UCLASS()
class FPS_API AMainLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class ALevelSequenceActor *EndingSequenceActor;
	class ALevelSequenceActor *GameOverSequenceActor;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence")
	class ULevelSequence *EndingSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence")
	class ULevelSequence *GameOverSequence;

	void PlayEndingSequence();
	void PlayGameOverSequence();
};
