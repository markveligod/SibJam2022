// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/GamePlayerController.h"
#include "Components/WarmManager.h"

AGamePlayerController::AGamePlayerController()
{
    this->WarmManager = CreateDefaultSubobject<UWarmManager>(FName("Warm Manager"));
}
