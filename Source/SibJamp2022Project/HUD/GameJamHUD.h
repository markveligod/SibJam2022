// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/HUD/DebugHUD.h"
#include "GameJamHUD.generated.h"

class ASibJamp2022ProjectGameModeBase;
/**
 * 
 */
UCLASS()
class SIBJAMP2022PROJECT_API AGameJamHUD : public ADebugHUD
{
	GENERATED_BODY()

protected:
    // Draw the HUD.
    virtual void DrawHUD() override;

    /** Overridable native event for when play begins for this actor. */
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ASibJamp2022ProjectGameModeBase* GameMode;
};
