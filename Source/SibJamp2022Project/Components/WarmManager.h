// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SibJamp2022ProjectGameModeBase.h"
#include "Components/ActorComponent.h"
#include "WarmManager.generated.h"

class AGamePlayerController;
class ASibJamp2022ProjectGameModeBase;
USTRUCT(BlueprintType)
struct FRangeTemperature : public FFloatInterval
{
    GENERATED_BODY()
    
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIBJAMP2022PROJECT_API UWarmManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWarmManager();

    // Get temperature from percent
    float CalculateTemperature() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Component", meta = (ClampMin = "0.1", ClampMax = "60.0",
        DisplayName = "Частота вызова", Units = "s"))
    float RateTimeCall = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Component", meta = (ClampMin = "0.1", ClampMax = "100.0",
        DisplayName = "Процент дамага", Units = "%"))
    float UnitDamage = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Component", meta = (ClampMin = "0.1", ClampMax = "100.0",
        DisplayName = "Диапозон температуры"))
    FRangeTemperature RangeTemperature;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Component", meta = (ClampMin = "0.1", ClampMax = "0.9",
        DisplayName = "Множитель температуры"))
    float MultiplierTemperature = 0.5f;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

    UPROPERTY()
    ASibJamp2022ProjectGameModeBase* GameMode;

    UPROPERTY()
    AGamePlayerController* PlayerController;
    
    // Current Percent warm
    float Percent = 100.0f;

    // Current damage
    float Damage = 0.0f;

    FTimerHandle TimerHandleDamage;
    
    // Reduce the temperature
    UFUNCTION()
    void ReduceTemperature();

    //
    UFUNCTION()
    void OnChangeGamePlayState(EStateGamePlay NewState);
};
