#include "Environment/MKOIDamageVolume.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "TimerManager.h"
#include "Effects/MKOIDamageGameplayEffect.h"
#include "Settings/MKOIGameplayTagsSettings.h"

AMKOIDamageVolume::AMKOIDamageVolume()
{
    OnActorBeginOverlap.AddDynamic(this, &AMKOIDamageVolume::OnActorEnterVolume);
    OnActorEndOverlap.AddDynamic(this, &AMKOIDamageVolume::OnActorExitVolume);
    DamageEffectClass = UMKOIDamageGameplayEffect::StaticClass();
}

void AMKOIDamageVolume::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(DamageTickTimerHandle, this, &AMKOIDamageVolume::ApplyDamage, DamageInterval, true);
}

void AMKOIDamageVolume::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    GetWorldTimerManager().ClearTimer(DamageTickTimerHandle);
}

void AMKOIDamageVolume::OnActorEnterVolume(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor != this)
    {
        ActorsToAddInNextTick.Add(OtherActor);
        ApplyDamageToActor(OtherActor);
    }
}

void AMKOIDamageVolume::OnActorExitVolume(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor != this)
    {
        OverlappingActors.Remove(OtherActor);
        ActorsToAddInNextTick.Remove(OtherActor);
    }
}

void AMKOIDamageVolume::ApplyDamage()
{
    for (AActor* Actor : OverlappingActors)
    {
        ApplyDamageToActor(Actor);
    }
    OverlappingActors.Append(ActorsToAddInNextTick);
    ActorsToAddInNextTick.Empty();
}

void AMKOIDamageVolume::ApplyDamageToActor(AActor* Actor)
{
	if (UAbilitySystemComponent* ASC = Actor->FindComponentByClass<UAbilitySystemComponent>())
	{
		FGameplayEffectContextHandle Context = ASC->MakeEffectContext();

		FGameplayEffectSpecHandle DamageSpecHandle = ASC->MakeOutgoingSpec(DamageEffectClass, 1.0f, Context);

		if (DamageSpecHandle.IsValid())
		{
			DamageSpecHandle.Data->SetSetByCallerMagnitude(GetDefault<UMKOIGameplayTagsSettings>()->DamageTag, DamagePerTick);

			ASC->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());
		}
	}
}
