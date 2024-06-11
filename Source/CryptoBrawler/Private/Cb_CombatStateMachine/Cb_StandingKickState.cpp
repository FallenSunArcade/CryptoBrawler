// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_CombatStateMachine/Cb_StandingKickState.h"
#include "Cb_Components/Cb_CombatComponent.h"
#include "Cb_ToolBox/Cb_CombatEnums.h"


void UCb_StandingKickState::EnterState(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	Super::EnterState(CombatComponent);
	
	if(CombatComponent)
	{
		CombatComponent->PlayCombatSequence(ESequenceName::StandingKick);
	}
}

void UCb_StandingKickState::SequenceEnded(TObjectPtr<UCb_CombatComponent> CombatComponent,
	const ESequenceName& SequenceName)
{
	Super::SequenceEnded(CombatComponent, SequenceName);

	if(SequenceName == ESequenceName::StandingKick)
	{
		CombatComponent->ChangeCurrentState(ECombatState::Standing);
	}
}
