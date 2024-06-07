// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_CombatStateMachine/Cb_StandingPunchState.h"
#include "Cb_Components/Cb_CombatComponent.h"


void UCb_StandingPunchState::EnterState(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	Super::EnterState(CombatComponent);

	if(CombatComponent)
	{
		CombatComponent->PlayCombatSequence(ESequenceName::StandingPunch);
	}
}

void UCb_StandingPunchState::SequenceEnded(TObjectPtr<UCb_CombatComponent> CombatComponent,
	const ESequenceName& SequenceName)
{
	Super::SequenceEnded(CombatComponent, SequenceName);

	if(SequenceName == ESequenceName::StandingPunch)
	{
		CombatComponent->ChangeCurrentState(ECombatState::Standing);
	}
}
