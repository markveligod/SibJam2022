// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MediaPlayer.h"
#include "UserWidgetBase.h"
#include "Components/Button.h"
#include "IntroUserWidget.generated.h"

class ASibJamp2022ProjectGameModeBase;
/**
 * 
 */
UCLASS()
class SIBJAMP2022PROJECT_API UIntroUserWidget : public UUserWidgetBase
{
	GENERATED_BODY()

protected:

    virtual void NativeOnInitialized() override;
    virtual void OnStart() override;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UMediaPlayer* MediaPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UMediaSource* MediaSource;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float VideoDuration = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient, meta = (BindWidget))
    UButton* SkipButton;
    
private:
    UPROPERTY()
    ASibJamp2022ProjectGameModeBase* GameMode;
    FTimerHandle TimerHandleNextState;

    UFUNCTION()
    void SkipVideo();
};
