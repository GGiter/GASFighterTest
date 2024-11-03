// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MKOIMovementEnums.generated.h"


UENUM(BlueprintType)
enum class EGait : uint8
{
	Walk,
	Run,
	Sprint,
};

UENUM(BlueprintType)
enum class EMKOIMovementMode : uint8
{
	OnGround,
	InAir,
};

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Idle,
	Moving,
};

UENUM(BlueprintType)
enum class ERotationMode : uint8
{
	OrientToMovement,
	Strafe,
};

UENUM(BlueprintType)
enum class EStance : uint8
{
	Stand,
	Crouch,
};
