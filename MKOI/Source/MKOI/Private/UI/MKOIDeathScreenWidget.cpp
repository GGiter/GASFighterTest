// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MKOIDeathScreenWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMKOIDeathScreenWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UMKOIDeathScreenWidget::OnRestartButtonPressed);
    }

    if(APlayerController* OwningPlayer = GetOwningPlayer())
        OwningPlayer->SetInputMode(FInputModeUIOnly());
}

void UMKOIDeathScreenWidget::OnRestartButtonPressed()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
