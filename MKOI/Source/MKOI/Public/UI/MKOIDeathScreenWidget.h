// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MKOIDeathScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class MKOI_API UMKOIDeathScreenWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual void NativeConstruct() override;

protected:
    UFUNCTION()
    void OnRestartButtonPressed();

    UPROPERTY(meta = (BindWidget))
    class UButton* RestartButton;	
};
