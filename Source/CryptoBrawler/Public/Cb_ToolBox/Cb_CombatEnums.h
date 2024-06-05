// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ECombatState : uint8
{
	Standing
};

UENUM(BlueprintType)
enum class ESequenceName : uint8
{
	Default,
	Punch,
	KnockBack
};