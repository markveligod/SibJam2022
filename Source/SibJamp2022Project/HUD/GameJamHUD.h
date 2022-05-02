// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SibJamp2022ProjectGameModeBase.h"
#include "Game/HUD/DebugHUD.h"
#include "GameJamHUD.generated.h"

class UUserWidgetBase;
/**
 * 
 */
UCLASS()
class SIBJAMP2022PROJECT_API AGameJamHUD : public ADebugHUD
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    TMap<EStateGamePlay, UUserWidgetBase*> GetRepoWidgets() const { return this->RepoWidgets; }
    
protected:
    // Draw the HUD.
    virtual void DrawHUD() override;

    /** Overridable native event for when play begins for this actor. */
    virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidgetBase> IntroWidget;
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidgetBase> GameWidget;
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidgetBase> WinWidget;
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidgetBase> LoseWidget;

private:

    UPROPERTY()
    TMap<EStateGamePlay, UUserWidgetBase*> RepoWidgets;

    UPROPERTY()
    UUserWidgetBase* VisibleWidget = nullptr;
    
    UPROPERTY()
    ASibJamp2022ProjectGameModeBase* GameMode;

    UFUNCTION()
    void OnGameStateChanged(EStateGamePlay NewState);

    void SetupNewWidget(UUserWidgetBase* NewWidget);
};
