// Fill out your copyright notice in the Description page of Project Settings.


#include "MKOIWeapon.h"

AMKOIWeapon::AMKOIWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;
    AttachSocketName = "SwordSocket";
}