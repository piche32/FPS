// Fill out your copyright notice in the Description page of Project Settings.

#include "MainLevelScriptActor.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"

void AMainLevelScriptActor::PlayEndingSequence()
{
    if (EndingSequence)
    {
        FMovieSceneSequencePlaybackSettings PlaybackSettings;
        PlaybackSettings.bDisableLookAtInput = true;
        PlaybackSettings.bDisableMovementInput = true;
        PlaybackSettings.bHideHud = true;
        ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), EndingSequence, PlaybackSettings, EndingSequenceActor);

        if (EndingSequenceActor)
        {
            EndingSequenceActor->AddBindingByTag(FName(TEXT("Player")), UGameplayStatics::GetPlayerPawn(GetWorld(), 0), false);
            EndingSequenceActor->SequencePlayer->Play();
        }
    }
}

void AMainLevelScriptActor::PlayGameOverSequence()
{
    if (GameOverSequence)
    {
        FMovieSceneSequencePlaybackSettings PlaybackSettings;
        PlaybackSettings.bDisableLookAtInput = true;
        PlaybackSettings.bDisableMovementInput = true;
        PlaybackSettings.bHideHud = true;
        ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), GameOverSequence, PlaybackSettings, GameOverSequenceActor);

        if (GameOverSequenceActor)
        {
            GameOverSequenceActor->SequencePlayer->Play();
        }
    }
}
