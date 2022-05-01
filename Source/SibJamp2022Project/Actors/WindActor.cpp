// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WindActor.h"
#include "Components/BoxComponent.h"
#include "Components/WindManager.h"
#include "Controller/GamePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Library/JamMSFunctionLibrary.h"

// Sets default values
AWindActor::AWindActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    this->RootScene = CreateDefaultSubobject<USceneComponent>(FName("Scene component"));
    SetRootComponent(this->RootScene);

    this->TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("Trigger box component"));
    this->TriggerBox->SetupAttachment(this->RootScene);

    this->RangeWind.Min = 5.0f;
    this->RangeWind.Max = 15.0f;
}

// Called when the game starts or when spawned
void AWindActor::BeginPlay()
{
	Super::BeginPlay();

    this->PlayerController = Cast<AGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (!CHECK(this->PlayerController != nullptr, FString("Player Controller is nullptr"))) return;
    OnActorBeginOverlap.AddDynamic(this, &AWindActor::RegisterBeginOverlap);
    OnActorEndOverlap.AddDynamic(this, &AWindActor::RegisterEndOverlap);
}

void AWindActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    if (this->TriggerBox)
    {
        this->TriggerBox->SetBoxExtent(this->TriggerBoxExtent);
    }
}

void AWindActor::RegisterBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (!OtherActor) return;
    if (!OtherActor->IsA(APawn::StaticClass())) return;
    if (this->PlayerController->GetPawn() != OtherActor) return;

    if (GetWorldTimerManager().TimerExists(this->TimerHandleStartWind))
    {
        GetWorldTimerManager().ClearTimer(this->TimerHandleStartWind);
    }
    GetWorldTimerManager().SetTimer(this->TimerHandleStartWind, this, &AWindActor::StartWind, this->RateCallStart, false);
}

void AWindActor::RegisterEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (!OtherActor) return;
    if (!OtherActor->IsA(APawn::StaticClass())) return;
    if (this->PlayerController->GetPawn() != OtherActor) return;

    ResetWind();
}

void AWindActor::StartWind()
{
    const float TimerRestartCall = UKismetMathLibrary::RandomFloatInRange(this->RangeWind.Min, this->RangeWind.Max);
    this->PlayerController->WindManager->StartWind(this->WindExposurePer, FMath::RandBool() ? EDirectionWind::Left : EDirectionWind::Right, TimerRestartCall);
    GetWorldTimerManager().ClearTimer(this->TimerHandleStartWind);
    GetWorldTimerManager().ClearTimer(this->TimerHandleRestartWind);
    GetWorldTimerManager().SetTimer(this->TimerHandleRestartWind, this, &AWindActor::RestartWind, TimerRestartCall);
}

void AWindActor::ResetWind()
{
    this->PlayerController->WindManager->ResetWind();
    GetWorldTimerManager().ClearTimer(this->TimerHandleRestartWind);
    GetWorldTimerManager().ClearTimer(this->TimerHandleStartWind);
}

void AWindActor::RestartWind()
{
    this->ResetWind();
    GetWorldTimerManager().SetTimer(this->TimerHandleStartWind, this, &AWindActor::StartWind, this->RateCallStart, false);
}

