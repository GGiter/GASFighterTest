// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "MKOIDamageExecution.generated.h"

/**
 * 
 */
UCLASS()
class MKOI_API UMKOIDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
    UMKOIDamageExecution();

protected:
    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
                                        FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;	
};
