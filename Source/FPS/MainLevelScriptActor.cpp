// Fill out your copyright notice in the Description page of Project Settings.

#include "MainLevelScriptActor.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"

void AMainLevelScriptActor::PlayEndingSequence()
{
    if (EndingSequence)
    {

        if (!SequenceActor)
        {
            FMovieSceneSequencePlaybackSettings PlaybackSettings;
            ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), EndingSequence, PlaybackSettings, SequenceActor);
        }

        if (SequenceActor)
        {
            SequenceActor->AddBindingByTag(FName(TEXT("Player")), UGameplayStatics::GetPlayerPawn(GetWorld(), 0), false);
            SequenceActor->SequencePlayer->Play();
        }
    }
}
