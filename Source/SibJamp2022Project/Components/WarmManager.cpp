// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WarmManager.h"

#include "Controller/GamePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Library/JamMSFunctionLibrary.h"

// Sets default values for this component's properties
UWarmManager::UWarmManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	RangeTemperature.Max = 36.7f;
    RangeTemperature.Min = 35.5f;
}

float UWarmManager::CalculateTemperature() const
{
    return UKismetMathLibrary::MapRangeClamped(this->Percent, 0.0f, 100.0f, this->RangeTemperature.Min, this->RangeTemperature.Max);
}

// Called when the game starts
void UWarmManager::BeginPlay()
{
	Super::BeginPlay();

    this->GameMode = ASibJamp2022ProjectGameModeBase::Get(GetWorld());
    if (!CHECK(this->GameMode != nullptr, FString("Game mode is nullptr"))) return;
    this->PlayerController = Cast<AGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (!CHECK(this->PlayerController != nullptr, FString("Player Controller is nullptr"))) return;
    
    this->GameMode->OnChangeGameState.AddDynamic(this, &UWarmManager::OnChangeGamePlayState);
    this->Damage = this->UnitDamage;
}

void UWarmManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (this->PlayerController->GetPawn()->GetVelocity().Size() > 300.0f)
    {
        this->Damage = this->UnitDamage * this->MultiplierTemperature;
    }
    else
    {
        this->Damage = this->UnitDamage;
    }
}

void UWarmManager::ReduceTemperature()
{
    this->Percent = FMath::Clamp(this->Percent - this->Damage, 0.0f, 100.0f);
    LOGJAM(ELogVerb::Display, FString::Printf(TEXT("New percent: %f"), this->Percent));
    if (this->Percent == 0.0f)
    {
        this->GameMode->ChangeGameState(EStateGamePlay::GameOver);
    }
}

void UWarmManager::OnChangeGamePlayState(EStateGamePlay NewState)
{
    if (GetWorld()->GetTimerManager().TimerExists(this->TimerHandleDamage))
    {
        GetWorld()->GetTimerManager().ClearTimer(this->TimerHandleDamage);
    }

    if (NewState == EStateGamePlay::GameProgress)
    {
       GetWorld()->GetTimerManager().SetTimer(this->TimerHandleDamage, this, &UWarmManager::ReduceTemperature, this->RateTimeCall, true);
    }
}
