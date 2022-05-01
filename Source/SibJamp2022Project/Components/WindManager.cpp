// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WindManager.h"

#include "Controller/GamePlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Library/JamMSFunctionLibrary.h"

// Sets default values for this component's properties
UWindManager::UWindManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UWindManager::StartWind(float NewPercentForce, EDirectionWind NewDirection, float NewRateTime)
{
    this->bIsWindStart = true;
    this->DirectionWind = NewDirection;
    this->PercentForce = NewPercentForce;
    this->RateTimerCallReset = NewRateTime;
}

void UWindManager::ResetWind()
{
    this->bIsWindStart = false;
    this->DirectionWind = EDirectionWind::None;
    this->PercentForce = 0.0f;
    this->PlayerController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = this->MaxSpeedReserve;
    this->RateTimerCallReset = 0.0f;
}


// Called when the game starts
void UWindManager::BeginPlay()
{
	Super::BeginPlay();

    this->PlayerController = Cast<AGamePlayerController>(GetOwner());
    if (!CHECK(this->PlayerController != nullptr, FString("Player Controller is nullptr"))) return;

    this->MaxSpeedReserve = this->PlayerController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed;
}


// Called every frame
void UWindManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->bIsWindStart)
	{
	    if (this->DirectionWind == EDirectionWind::Right)
	    {
	        if (this->PlayerController->GetCharacter()->GetVelocity().Y > 0)
	        {
	            this->PlayerController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = this->MaxSpeedReserve * 1.5f * (1 + (this->PercentForce / 200.0f)); 
	        }
            else
            {
                this->PlayerController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = this->MaxSpeedReserve * 1.5f * (1 - (this->PercentForce / 100.0f)); 
            }
	    }
        else if (this->DirectionWind == EDirectionWind::Left)
        {
            if (this->PlayerController->GetCharacter()->GetVelocity().Y <= 0)
            {
                this->PlayerController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = this->MaxSpeedReserve * 1.5f * (1 + (this->PercentForce / 200.0f)); 
            }
            else
            {
                this->PlayerController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = this->MaxSpeedReserve * 1.5f * (1 - (this->PercentForce / 100.0f)); 
            }
        }
	}
}

