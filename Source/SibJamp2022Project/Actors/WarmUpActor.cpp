// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WarmUpActor.h"
#include "Components/BoxComponent.h"
#include "Components/WarmManager.h"
#include "Controller/GamePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Library/JamMSFunctionLibrary.h"

// Sets default values
AWarmUpActor::AWarmUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    this->RootScene = CreateDefaultSubobject<USceneComponent>(FName("Scene component"));
    SetRootComponent(this->RootScene);

    this->StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static mesh component"));
    this->StaticMesh->SetupAttachment(this->RootScene);

    this->TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("Trigger box component"));
    this->TriggerBox->SetupAttachment(this->RootScene);
}

// Called when the game starts or when spawned
void AWarmUpActor::BeginPlay()
{
	Super::BeginPlay();

    this->PlayerController = Cast<AGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (!CHECK(this->PlayerController != nullptr, FString("Player Controller is nullptr"))) return;
    
    OnActorBeginOverlap.AddDynamic(this, &AWarmUpActor::RegisterBeginOverlap);
    OnActorEndOverlap.AddDynamic(this, &AWarmUpActor::RegisterEndOverlap);
}

void AWarmUpActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (this->TriggerBox)
    {
        this->TriggerBox->SetBoxExtent(this->TriggerBoxExtent);
    }

    if (this->StaticMesh)
    {
        this->StaticMesh->SetStaticMesh(this->Mesh);
    }
}

void AWarmUpActor::RegisterBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (!OtherActor) return;
    if (!OtherActor->IsA(APawn::StaticClass())) return;
    if (this->PlayerController->GetPawn() != OtherActor) return;
    
    this->PlayerController->WarmManager->ResetTimerDamage();
    if (GetWorldTimerManager().TimerExists(this->TimerHandleUpWarm))
    {
        GetWorldTimerManager().ClearTimer(this->TimerHandleUpWarm);
    }
    FTimerDelegate TimerDelegate;
    TimerDelegate.BindUObject(this->PlayerController->WarmManager, &UWarmManager::WarmUpper, this->UnitUpWarm);
    GetWorldTimerManager().SetTimer(this->TimerHandleUpWarm, TimerDelegate, this->RateTimeCall, true);
}

void AWarmUpActor::RegisterEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (!OtherActor) return;
    if (!OtherActor->IsA(APawn::StaticClass())) return;
    if (this->PlayerController->GetPawn() != OtherActor) return;

    if (GetWorldTimerManager().TimerExists(this->TimerHandleUpWarm))
    {
        GetWorldTimerManager().ClearTimer(this->TimerHandleUpWarm);
    }
    this->PlayerController->WarmManager->StartTimerDamage();
}


