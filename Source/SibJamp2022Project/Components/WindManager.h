// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WindManager.generated.h"

class AGamePlayerController;
UENUM(BlueprintType)
enum class EDirectionWind: uint8
{
    None,
    Right,
    Left
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIBJAMP2022PROJECT_API UWindManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWindManager();

    void StartWind(float NewPercentForce, EDirectionWind NewDirection, float NewRateTime);
    void ResetWind();

    UPROPERTY(BlueprintReadOnly)
    EDirectionWind DirectionWind = EDirectionWind::None;
    UPROPERTY(BlueprintReadOnly)
    float PercentForce;
    float RateTimerCallReset;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
    UPROPERTY()
    AGamePlayerController* PlayerController = nullptr;
    bool bIsWindStart = false;

    float MaxSpeedReserve = 0.0f;
};
