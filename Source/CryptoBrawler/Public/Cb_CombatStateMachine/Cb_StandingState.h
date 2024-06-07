// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cb_CombatState.h"
#include "Cb_StandingState.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTOBRAWLER_API UCb_StandingState : public UCb_CombatState
{
	GENERATED_BODY()

public:
	virtual void EnterState(TObjectPtr<UCb_CombatComponent> CombatComponent) override;

	virtual void Punch(TObjectPtr<UCb_CombatComponent> CombatComponent) override;

	virtual void KnockBack(TObjectPtr<UCb_CombatComponent> CombatComponent) override;
};
