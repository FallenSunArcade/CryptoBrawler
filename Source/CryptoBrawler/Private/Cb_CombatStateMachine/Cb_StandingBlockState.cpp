// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_CombatStateMachine/Cb_StandingBlockState.h"
#include "Cb_Components/Cb_CombatComponent.h"


void UCb_StandingBlockState::EnterState(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	Super::EnterState(CombatComponent);

	CombatComponent->SetCurrentCombatMode(ECombatMode::StandingBlock);
}

void UCb_StandingBlockState::EnterCombatMode(TObjectPtr<UCb_CombatComponent> CombatComponent,
                                             const ECombatMode& CombatMode)
{
	Super::EnterCombatMode(CombatComponent, CombatMode);

	if (CombatMode == ECombatMode::Standing)
	{
		CombatComponent->ChangeCurrentState(ECombatState::Standing);
	}
}
