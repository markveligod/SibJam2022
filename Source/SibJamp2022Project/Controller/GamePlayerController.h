// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

class UWindManager;
class UWarmManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractSignature);

/**
 * 
 */
UCLASS()
class SIBJAMP2022PROJECT_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

    AGamePlayerController();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UWarmManager* WarmManager;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UWindManager* WindManager;

    virtual void SetupInputComponent() override;

    FInteractSignature OnInteract;

private:
    void RegisterInteract();
};
