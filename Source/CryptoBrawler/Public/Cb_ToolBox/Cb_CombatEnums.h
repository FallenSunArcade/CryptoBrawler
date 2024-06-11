// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ECombatMode : uint8
{
	Standing,
	StandingBlock,
	Crouching,
	CrouchingBlock
};

UENUM(BlueprintType)
enum class ECombatState : uint8
{
	Standing,
	StandingPunch,
	StandingKnockBack,
	StandingKick,
	StandingBlock
};

UENUM(BlueprintType)
enum class ESequenceName : uint8
{
	None,
	StandingPunch,
	StandingKnockBack,
	StandingKick
};