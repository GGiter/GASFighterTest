// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "AbilitySystemInterface.h"
#include "MKOIDamageVolume.generated.h"

class UGameplayEffect;

UCLASS()
class MKOI_API AMKOIDamageVolume : public AVolume
{
	GENERATED_BODY()

public:
    AMKOIDamageVolume();

protected:
    // The damage to be applied per tick
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
    float DamagePerTick = 10.0f;

    // Time interval between damage applications
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
    float DamageInterval = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
    TSubclassOf<UGameplayEffect> DamageEffectClass;

    FTimerHandle DamageTickTimerHandle;

    void ApplyDamage();
    void ApplyDamageToActor(AActor* Actor);

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION()
    void OnActorEnterVolume(AActor* OverlappedActor, AActor* OtherActor);

    UFUNCTION()
    void OnActorExitVolume(AActor* OverlappedActor, AActor* OtherActor);

private:
    TArray<AActor*> OverlappingActors;
    TArray<AActor*> ActorsToAddInNextTick;
};
