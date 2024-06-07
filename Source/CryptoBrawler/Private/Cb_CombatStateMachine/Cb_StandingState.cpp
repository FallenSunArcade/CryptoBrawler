// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_CombatStateMachine/Cb_StandingState.h"
#include "Cb_Components/Cb_CombatComponent.h"


void UCb_StandingState::EnterState(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	Super::EnterState(CombatComponent);
}

void UCb_StandingState::Punch(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	Super::Punch(CombatComponent);

	if(CombatComponent)
	{
		CombatComponent->ChangeCurrentState(ECombatState::StandingPunch);
	}
}

void UCb_StandingState::KnockBack(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	Super::KnockBack(CombatComponent);

	if(CombatComponent)
	{
		CombatComponent->ChangeCurrentState(ECombatState::StandingKnockBack);
	}
}
