// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_CombatStateMachine/Cb_CombatStateMachine.h"

#include "Cb_CombatStateMachine/Cb_StandingBlockState.h"
#include "Cb_CombatStateMachine/Cb_StandingKickState.h"
#include "Cb_CombatStateMachine/Cb_StandingKnockBackState.h"
#include "Cb_CombatStateMachine/Cb_StandingPunchState.h"
#include "Cb_CombatStateMachine/Cb_StandingState.h"
#include "Cb_ToolBox/Cb_CombatEnums.h"
#include "Cb_ToolBox/Cb_LogCategories.h"


void UCb_CombatStateMachine::GenerateStates()
{
	if(StateMap.IsEmpty())
	{
		StateMap.Emplace(ECombatState::Standing, NewObject<UCb_StandingState>());
		StateMap.Emplace(ECombatState::StandingPunch, NewObject<UCb_StandingPunchState>());
		StateMap.Emplace(ECombatState::StandingKnockBack, NewObject<UCb_StandingKnockBackState>());
		StateMap.Emplace(ECombatState::StandingKick, NewObject<UCb_StandingKickState>());
		StateMap.Emplace(ECombatState::StandingBlock, NewObject<UCb_StandingBlockState>());
	}
}

TObjectPtr<UCb_CombatState> UCb_CombatStateMachine::ChangeState(const ECombatState& State)
{
	if(StateMap.Find(State))
	{
		return StateMap[State];
	}
	
	UE_LOG(LogCb, Warning, TEXT("[%s] %s Key not found"), *GetName(), *UEnum::GetValueAsString(State));
	return nullptr;
}
