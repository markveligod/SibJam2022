// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/UI/IntroUserWidget.h"
#include "SibJamp2022ProjectGameModeBase.h"
#include "Library/JamMSFunctionLibrary.h"

void UIntroUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    this->SkipButton->OnClicked.AddDynamic(this, &UIntroUserWidget::SkipVideo);
    this->SkipButton->SetVisibility(ESlateVisibility::Hidden);
    this->GameMode = ASibJamp2022ProjectGameModeBase::Get(GetWorld());
    if (!CHECK(this->GameMode != nullptr, FString("Game mode is nullptr"))) return;

}

void UIntroUserWidget::OnStart()
{
    Super::OnStart();

    FTimerHandle TimerHandleButton;
    FTimerDelegate TimerDelegateButton;
    TimerDelegateButton.BindLambda([this]()
    {
        this->SkipButton->SetVisibility(ESlateVisibility::Visible);
    });
    GetWorld()->GetTimerManager().SetTimer(TimerHandleButton, TimerDelegateButton, 5.0f, false);
    
    if (this->MediaPlayer && this->MediaSource)
    {
        this->MediaPlayer->OpenSource(this->MediaSource);
        FTimerDelegate TimerDelegateMedia;
       
        TimerDelegateMedia.BindUObject(this->GameMode, &ASibJamp2022ProjectGameModeBase::ChangeGameState, EStateGamePlay::GameProgress);
        GetWorld()->GetTimerManager().SetTimer(this->TimerHandleNextState, TimerDelegateMedia, this->VideoDuration + 0.5f, false);
    }
}

void UIntroUserWidget::SkipVideo()
{
    GetWorld()->GetTimerManager().ClearTimer(this->TimerHandleNextState);
    this->GameMode->ChangeGameState(EStateGamePlay::GameProgress);
}
