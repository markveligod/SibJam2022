// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgetBase.h"
#include "GameWinUserWidget.generated.h"

class ASibJamp2022ProjectGameModeBase;
class UMediaSource;
class UMediaPlayer;
/**
 * 
 */
UCLASS()
class SIBJAMP2022PROJECT_API UGameWinUserWidget : public UUserWidgetBase
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
    
private:
    UPROPERTY()
    ASibJamp2022ProjectGameModeBase* GameMode;
};
