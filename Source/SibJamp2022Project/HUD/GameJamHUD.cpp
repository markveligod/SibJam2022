// Fill out your copyright notice in the Description page of Project Settings.

#include "GameJamHUD.h"

#include "Components/WarmManager.h"
#include "Components/WindManager.h"
#include "Kismet/GameplayStatics.h"
#include "Library/JamMSFunctionLibrary.h"
#include "SibJamp2022Project/SibJamp2022ProjectGameModeBase.h"

inline void AGameJamHUD::DrawHUD()
{
    Super::DrawHUD();
#if UE_EDITOR
    if (this->GameMode && EnableDebugHUD)
    {
        AddText(TEXT("----Stat Pawn----"), FText());
        FVector Loc = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();
        AddText(TEXT("Location:"), FText::FromString(Loc.ToString()));
        FVector Velocity = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetVelocity();
        AddText(TEXT("Vector velocity:"), FText::FromString(Velocity.ToString()));
        const float SpeedPawn = Velocity.Size();
        AddFloat(TEXT("Speed:"), SpeedPawn);
        UWarmManager* WM = Cast<UWarmManager>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetComponentByClass(UWarmManager::StaticClass()));
        AddFloat(TEXT("Temperature:"), WM->CalculateTemperature());
        
        AddText(TEXT("----Stat Game mode----"), FText());
        AddText(TEXT("Game play state:"), FText::FromString(UEnum::GetValueAsString(this->GameMode->GetStateGamePlay())));
        
        UWindManager* Wind = Cast<UWindManager>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetComponentByClass(UWindManager::StaticClass()));
        AddText(TEXT("Wind direction:"), FText::FromString(UEnum::GetValueAsString(Wind->DirectionWind)));
        AddFloat(TEXT("Force percent:"), Wind->PercentForce);
        AddFloat(TEXT("Restart to wind:"), Wind->RateTimerCallReset);
        
    }
#endif
}

inline void AGameJamHUD::BeginPlay()
{
    Super::BeginPlay();

    this->GameMode = ASibJamp2022ProjectGameModeBase::Get(GetWorld());
    if (!CHECK(this->GameMode != nullptr, FString("Game mode is nullptr"))) return;
}