// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_CombatStateMachine/Cb_CombatState.h"
#include "Cb_ToolBox/Cb_LogCategories.h"


void UCb_CombatState::EnterState(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	UE_LOG(LogCbCombat, Display, TEXT("[%s] EnterState"), *GetName());
}

void UCb_CombatState::ExitState(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	UE_LOG(LogCbCombat, Display, TEXT("[%s] ExitState"), *GetName());
}

void UCb_CombatState::SequenceEnded(TObjectPtr<UCb_CombatComponent> CombatComponent, const ESequenceName& SequenceName)
{
	UE_LOG(LogCbCombat, Display, TEXT("[%s] SequenceEnded (%s)"), *GetName(), *UEnum::GetValueAsString(SequenceName));
}

void UCb_CombatState::Punch(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	UE_LOG(LogCbCombat, Display, TEXT("[%s] Punch"), *GetName());
}

void UCb_CombatState::KnockBack(TObjectPtr<UCb_CombatComponent> CombatComponent)
{
	UE_LOG(LogCbCombat, Display, TEXT("[%s] KnockBack"), *GetName());
}
