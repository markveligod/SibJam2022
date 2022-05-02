// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/UI/GameLoseUserWidget.h"

#include "JamMSGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Library/JamMSFunctionLibrary.h"

void UGameLoseUserWidget::OnStart()
{
    Super::OnStart();

    UJamMSGameInstance* GameInst = UJamMSGameInstance::Get(GetWorld());
    if (!CHECK(GameInst != nullptr, FString("Game inst is nullptr"))) return;

    ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    Character->GetCharacterMovement()->DisableMovement();
    Character->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    Character->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Character->GetMesh()->SetSimulatePhysics(true);
    
    PlayAnimation(this->LoseAnim);
    const float EndTime = this->LoseAnim->GetEndTime();
    FTimerHandle TimerHandle;
    FTimerDelegate TimerDelegate;
    TimerDelegate.BindLambda([this, GameInst]()
    {
        UGameplayStatics::OpenLevel(GetWorld(), GameInst->GetNameStartLevel());
    });

    GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, EndTime, false);
}
