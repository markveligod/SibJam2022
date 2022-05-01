// Copyright Epic Games, Inc. All Rights Reserved.


#include "SibJamp2022ProjectGameModeBase.h"

#include "Library/JamMSFunctionLibrary.h"

void ASibJamp2022ProjectGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    ChangeGameState(EStateGamePlay::Intro);
}

void ASibJamp2022ProjectGameModeBase::ChangeGameState(EStateGamePlay NewState)
{
    if (this->StateGamePlay == NewState)
    {
        LOGJAM(ELogVerb::Warning, FString::Printf(TEXT("Current game state: %s == New State: %s"),
            *UEnum::GetValueAsString(this->StateGamePlay), *UEnum::GetValueAsString(NewState)));
        return;
    }

    this->StateGamePlay = NewState;
    this->OnChangeGameState.Broadcast(NewState);
}
