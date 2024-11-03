// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "MKOIAnimNotifyState_GrantTagToAbility.generated.h"

/**
 * 
 */
UCLASS()
class MKOI_API UMKOIAnimNotifyState_GrantTagToAbility : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags")
    FGameplayTag TagToGrant;
};
