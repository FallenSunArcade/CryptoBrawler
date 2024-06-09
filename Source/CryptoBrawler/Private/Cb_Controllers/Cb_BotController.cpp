// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Controllers/Cb_BotController.h"
#include "BehaviorTree/BlackboardComponent.h"


ACb_BotController::ACb_BotController()
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentState = EBotState::Defending;
}

void ACb_BotController::SetBotState(const EBotState& State)
{
	if(GetBlackboardComponent())
	{
		CurrentState = State;
		GetBlackboardComponent()->SetValueAsEnum("BotState", static_cast<uint8>(State));
	}
}

void ACb_BotController::BeginPlay()
{
	Super::BeginPlay();

	if(CurrentBehaviorTree)
	{
		RunBehaviorTree(CurrentBehaviorTree);
	}

	SetBotState(CurrentState);

	GenerateRandomSwitchTimer();
}

void ACb_BotController::HandleSwitchState()
{
	if(CurrentState == EBotState::Attacking)
	{
		SetBotState(EBotState::Defending);
	}
	else
	{
		SetBotState(EBotState::Attacking);
	}

	GenerateRandomSwitchTimer();
}


void ACb_BotController::GenerateRandomSwitchTimer()
{
	float InRate =  3.f + FMath::RandRange(0.f, 5.f);
	
	GetWorldTimerManager().SetTimer(RandomSwitchStateHandle, this,
	&ACb_BotController::HandleSwitchState, InRate);
}
