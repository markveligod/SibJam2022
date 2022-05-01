// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarmUpActor.generated.h"

class AGamePlayerController;
class UBoxComponent;
UCLASS()
class SIBJAMP2022PROJECT_API AWarmUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarmUpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootScene = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* StaticMesh = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* TriggerBox = nullptr;

    virtual void OnConstruction(const FTransform& Transform) override;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Actor Settings", meta = (DisplayName = "Размер триггера"))
    FVector TriggerBoxExtent = FVector(100.0f);

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Actor Settings", meta = (DisplayName = "Мэш объекта"))
    UStaticMesh* Mesh = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor Settings", meta = (ClampMin = "0.1", ClampMax = "60.0",
        DisplayName = "Частота вызова", Units = "s"))
    float RateTimeCall = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor Settings", meta = (ClampMin = "0.1", ClampMax = "100.0",
        DisplayName = "Процент восстановления", Units = "%"))
    float UnitUpWarm = 1.0f;

    
private:
    UPROPERTY()
    AGamePlayerController* PlayerController = nullptr;

    UFUNCTION()
    void RegisterBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

    UFUNCTION()
    void RegisterEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

    
    FTimerHandle TimerHandleUpWarm;
};
