 // Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_BTTask/Cb_MoveToPlayer.h"
#include "AIController.h"
#include "Cb_Characters/Cb_Bot.h"
#include "Cb_ToolBox/Cb_LogCategories.h"


 UCb_MoveToPlayer::UCb_MoveToPlayer()
 {
 	NodeName = TEXT("Move To Player");
 	bCreateNodeInstance = true;
 }

 EBTNodeResult::Type UCb_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
 {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	const AAIController* AIController = OwnerComp.GetAIOwner();
 	
	if (!AIController)
	{
		UE_LOG(LogCbAI, Warning, TEXT("[%s] AIController is %p"), *GetName(), AIController);
		return EBTNodeResult::Failed;
	}

	ACb_Bot* Character = Cast<ACb_Bot>(AIController->GetPawn());
	if (!Character)
	{
		UE_LOG(LogCbAI, Warning, TEXT("[%s] Character is %p"), *GetName(), Character);
		return EBTNodeResult::Failed;
	}

	Character->MoveToPlayer(AcceptableDistance);

	return EBTNodeResult::Succeeded;
 }

 EBTNodeResult::Type UCb_MoveToPlayer::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
 {
  return Super::AbortTask(OwnerComp, NodeMemory);
 }
