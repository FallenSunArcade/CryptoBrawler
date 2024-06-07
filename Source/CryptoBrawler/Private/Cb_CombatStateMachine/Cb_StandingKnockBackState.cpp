// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_CombatStateMachine/Cb_StandingKnockBackState.h"

#include "Cb_Components/Cb_CombatComponent.h"

void UCb_StandingKnockBackState::EnterState(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	Super::EnterState(CombatComponent);

	if(CombatComponent)
	{
		CombatComponent->PlayCombatSequence(ESequenceName::StandingKnockBack);
	}
}

void UCb_StandingKnockBackState::SequenceEnded(TObjectPtr<UCb_CombatComponent> CombatComponent,
	const ESequenceName& SequenceName)
{
	Super::SequenceEnded(CombatComponent, SequenceName);

	if(SequenceName == ESequenceName::StandingKnockBack)
	{
		CombatComponent->ChangeCurrentState(ECombatState::Standing);
	}
}
