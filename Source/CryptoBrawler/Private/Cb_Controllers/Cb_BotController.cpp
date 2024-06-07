// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Controllers/Cb_BotController.h"
#include "BehaviorTree/BlackboardComponent.h"


ACb_BotController::ACb_BotController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACb_BotController::BeginPlay()
{
	Super::BeginPlay();

	if(CurrentBehaviorTree)
	{
		RunBehaviorTree(CurrentBehaviorTree);
	}
}