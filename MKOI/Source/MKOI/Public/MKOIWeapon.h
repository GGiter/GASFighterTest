// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MKOIWeapon.generated.h"

UCLASS()
class MKOI_API AMKOIWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AMKOIWeapon();

	UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
	FName GetAttackSocketName() const { return AttachSocketName; }
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName AttachSocketName;
};
