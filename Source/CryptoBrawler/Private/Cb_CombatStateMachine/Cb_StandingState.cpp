// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_CombatStateMachine/Cb_StandingState.h"
#include "Cb_Components/Cb_CombatComponent.h"


void UCb_StandingState::EnterState(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	Super::EnterState(CombatComponent);
	
	CombatComponent->SetCurrentCombatMode(ECombatMode::Standing);
}

void UCb_StandingState::Punch(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	Super::Punch(CombatComponent);
	
	CombatComponent->ChangeCurrentState(ECombatState::StandingPunch);
}

void UCb_StandingState::Kick(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	Super::Kick(CombatComponent);
	
	CombatComponent->ChangeCurrentState(ECombatState::StandingKick);
}

void UCb_StandingState::KnockBack(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	Super::KnockBack(CombatComponent);
	
	CombatComponent->ChangeCurrentState(ECombatState::StandingKnockBack);
}

void UCb_StandingState::EnterCombatMode(TObjectPtr<UCb_CombatComponent> CombatComponent,
	const ECombatMode& CombatMode)
{
	Super::EnterCombatMode(CombatComponent, CombatMode);

	if(CombatMode == ECombatMode::StandingBlock)
	{
		CombatComponent->ChangeCurrentState(ECombatState::StandingBlock);
	}
}

bool UCb_StandingState::CanMove()
{
	return true;
}
