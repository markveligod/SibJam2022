// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

class UWarmManager;
/**
 * 
 */
UCLASS()
class SIBJAMP2022PROJECT_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

    AGamePlayerController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UWarmManager* WarmManager;
};
