// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SibJamp2022ProjectGameModeBase.generated.h"

UENUM(BlueprintType)
enum EStateGamePlay
{
    None = 0,
    Intro,
    GameProgress,
    GameWin,
    GameLose
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameStateSignature, EStateGamePlay, GameState);

/**
 * 
 */
UCLASS()
class SIBJAMP2022PROJECT_API ASibJamp2022ProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    // Get singleton class
    static ASibJamp2022ProjectGameModeBase* Get(UWorld* World) { return (World) ? Cast<ASibJamp2022ProjectGameModeBase>(World->GetAuthGameMode()) : nullptr; }

    virtual void BeginPlay() override;
    
    FGameStateSignature OnChangeGameState;

    UFUNCTION(BlueprintCallable)
    void ChangeGameState(EStateGamePlay NewState);

    UFUNCTION(BlueprintPure)
    FORCEINLINE EStateGamePlay GetStateGamePlay() const { return this->StateGamePlay; }
    
private:
    EStateGamePlay StateGamePlay = EStateGamePlay::None;
    
};
