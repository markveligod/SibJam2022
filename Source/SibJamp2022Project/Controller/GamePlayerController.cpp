// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/GamePlayerController.h"
#include "Components/WarmManager.h"
#include "Components/WindManager.h"
#include "Library/JamMSFunctionLibrary.h"

AGamePlayerController::AGamePlayerController()
{
    this->WarmManager = CreateDefaultSubobject<UWarmManager>(FName("Warm Manager"));
    this->WindManager = CreateDefaultSubobject<UWindManager>(FName("Wind Manager"));
}

void AGamePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // If we have a valid InputComponent...
    if (InputComponent)
    {
        // Bind an action to it
        InputComponent->BindAction("Interact",IE_Pressed,this, &AGamePlayerController::RegisterInteract); 
    }
}

void AGamePlayerController::RegisterInteract()
{
    LOGJAM(ELogVerb::Display, "Press interact");
    OnInteract.Broadcast();
}
