// Fill out your copyright notice in the Description page of Project Settings.

#include "GameJamHUD.h"
#include "Components/CapsuleComponent.h"
#include "Components/WarmManager.h"
#include "Components/WindManager.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Library/JamMSFunctionLibrary.h"
#include "SibJamp2022Project/SibJamp2022ProjectGameModeBase.h"
#include "UI/UserWidgetBase.h"

void AGameJamHUD::DrawHUD()
{
    Super::DrawHUD();
#if UE_EDITOR
    if (this->GameMode && EnableDebugHUD && this->GameMode->GetStateGamePlay() == EStateGamePlay::GameProgress)
    {
        AddText(TEXT("----Stat Pawn----"), FText());
        FVector Loc = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();
        FRotator RotCap = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter()->GetCapsuleComponent()->GetComponentRotation();
        AddText(TEXT("Location:"), FText::FromString(Loc.ToString()));
        AddText(TEXT("Capsule rotation:"), FText::FromString(RotCap.ToString()));
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

void AGameJamHUD::BeginPlay()
{
    Super::BeginPlay();

    this->GameMode = ASibJamp2022ProjectGameModeBase::Get(GetWorld());
    if (!CHECK(this->GameMode != nullptr, FString("Game mode is nullptr"))) return;

    
    this->RepoWidgets.Add(EStateGamePlay::Intro,CreateWidget<UUserWidgetBase>(GetWorld(), this->IntroWidget));
    this->RepoWidgets.Add(EStateGamePlay::GameProgress,CreateWidget<UUserWidgetBase>(GetWorld(), this->GameWidget));
    this->RepoWidgets.Add(EStateGamePlay::GameWin,CreateWidget<UUserWidgetBase>(GetWorld(), this->WinWidget));
    this->RepoWidgets.Add(EStateGamePlay::GameLose,CreateWidget<UUserWidgetBase>(GetWorld(), this->LoseWidget));
    
    for (const auto Widget : this->RepoWidgets)
    {
        const auto ValueWidget = Widget.Value;
        ValueWidget->AddToViewport();
        ValueWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    this->GameMode->OnChangeGameState.AddDynamic(this, &AGameJamHUD::OnGameStateChanged);
}

void AGameJamHUD::OnGameStateChanged(EStateGamePlay NewState)
{
    LOGJAM(ELogVerb::Display, FString::Printf(TEXT("New State in HUD: %s"), *UEnum::GetValueAsString(NewState)));

    if (!CHECK(this->RepoWidgets.Contains(NewState), FString::Printf(TEXT("State: %s don't contains in TMap widgets"),
        *UEnum::GetValueAsString(NewState)))) return;
    
    if (this->VisibleWidget)
    {
        this->VisibleWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    this->SetupNewWidget(this->RepoWidgets[NewState]);

}

void AGameJamHUD::SetupNewWidget(UUserWidgetBase* NewWidget)
{
    this->VisibleWidget = NewWidget;
    this->VisibleWidget->OnStart();
    this->VisibleWidget->SetVisibility(ESlateVisibility::Visible);
}
