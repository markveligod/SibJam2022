// Copyright Epic Games, Inc. All Rights Reserved.


#include "SibJamp2022ProjectGameModeBase.h"

#include "Library/JamMSFunctionLibrary.h"

void ASibJamp2022ProjectGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle TimerHandle;
    FTimerDelegate TimerDelegate;
    TimerDelegate.BindLambda([this]()
    {
        ChangeGameState(EStateGamePlay::GameProgress);
    });
    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.0f, false);
}

void ASibJamp2022ProjectGameModeBase::ChangeGameState(EStateGamePlay NewState)
{
    if (this->StateGamePlay == NewState)
    {
        LOGJAM(ELogVerb::Warning, FString::Printf(TEXT("Current game state: %s == New State: %s"),
            *UEnum::GetValueAsString(this->StateGamePlay), *UEnum::GetValueAsString(NewState)));
        return;
    }

    LOGJAM(ELogVerb::Display, FString::Printf(TEXT("New game play state: %s"), *UEnum::GetValueAsString(NewState)));
    this->StateGamePlay = NewState;
    this->OnChangeGameState.Broadcast(NewState);
}
