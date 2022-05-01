// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WindActor.generated.h"

// wind operation range
USTRUCT(BlueprintType)
struct FRangeWind : public FFloatInterval
{
    GENERATED_BODY()
    
};

class AGamePlayerController;
class UBoxComponent;
UCLASS()
class SIBJAMP2022PROJECT_API AWindActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWindActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    virtual void OnConstruction(const FTransform& Transform) override;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Actor Settings", meta = (DisplayName = "Размер триггера"))
    FVector TriggerBoxExtent = FVector(100.0f);
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* TriggerBox = nullptr;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Actor Settings", meta = (DisplayName = "Длительность ветра"))
    FRangeWind RangeWind;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Actor Settings", meta = (DisplayName = "Период бездействия ветра",
        Units = "s", ClampMin = "1.0", ClampMax = "100.0"))
    float RateCallStart = 5.0f;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Actor Settings", meta = (DisplayName = "Процент воздействия ветра",
        Units = "%", ClampMin = "1.0", ClampMax = "100.0"))
    float WindExposurePer = 70.0f;
    
private:
    UPROPERTY()
    AGamePlayerController* PlayerController = nullptr;
    
    UFUNCTION()
    void RegisterBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

    UFUNCTION()
    void RegisterEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

    FTimerHandle TimerHandleStartWind;
    FTimerHandle TimerHandleRestartWind;

    void StartWind();
    void ResetWind();
    void RestartWind();
};
