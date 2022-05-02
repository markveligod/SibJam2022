// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/UI/GameWinUserWidget.h"

#include "JamMSGameInstance.h"
#include "MediaPlayer.h"
#include "SibJamp2022ProjectGameModeBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Library/JamMSFunctionLibrary.h"

void UGameWinUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    this->GameMode = ASibJamp2022ProjectGameModeBase::Get(GetWorld());
    if (!CHECK(this->GameMode != nullptr, FString("Game mode is nullptr"))) return;
}

void UGameWinUserWidget::OnStart()
{
    Super::OnStart();

    UJamMSGameInstance* GameInst = UJamMSGameInstance::Get(GetWorld());
    if (!CHECK(GameInst != nullptr, FString("Game inst is nullptr"))) return;

    
    if (this->MediaPlayer && this->MediaSource)
    {
        ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        Character->GetCharacterMovement()->DisableMovement();
    
        this->MediaPlayer->OpenSource(this->MediaSource);

        FTimerHandle TimerHandle;
        FTimerDelegate TimerDelegateMedia;
        TimerDelegateMedia.BindLambda([this, GameInst]()
        {
            UGameplayStatics::OpenLevel(GetWorld(), GameInst->GetNameMenuLevel());
        });
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegateMedia, this->VideoDuration + 1.5f, false);
    }
}
