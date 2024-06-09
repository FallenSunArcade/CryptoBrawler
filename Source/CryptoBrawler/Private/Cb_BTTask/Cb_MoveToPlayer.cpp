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

 	BTComponent = OwnerComp;
 	
	const AAIController* AIController = OwnerComp.GetAIOwner();
 	
	if (!AIController)
	{
		UE_LOG(LogCbAI, Warning, TEXT("[%s] AIController is %p"), *GetName(), AIController);
		return EBTNodeResult::Failed;
	}

	BotRef = Cast<ACb_Bot>(AIController->GetPawn());
	if (!BotRef)
	{
		UE_LOG(LogCbAI, Warning, TEXT("[%s] Character is %p"), *GetName(), BotRef.Get());
		return EBTNodeResult::Failed;
	}

 	if(bIsMoveAway)
 	{
 		BotRef->MoveAwayFromPlayer(AcceptableDistance);
 	}
    else
    {
    	BotRef->MoveToPlayer(AcceptableDistance);
    }

 	BotRef->OnReachedDestination.AddDynamic(this, &UCb_MoveToPlayer::OnDestinationReached);

	return EBTNodeResult::InProgress;
 }

 EBTNodeResult::Type UCb_MoveToPlayer::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
 {
 	CleanUp();
 	return EBTNodeResult::Aborted;
 }

 void UCb_MoveToPlayer::OnDestinationReached(bool DestinationReached)
 {
 	if (BTComponent)
 	{
 		UE_LOG(LogCbAI, Display, TEXT("[%s] OnDestinationReached"), *GetName());
 		CleanUp();
 		FinishLatentTask(*BTComponent, EBTNodeResult::Succeeded);
 	}
 }

 void UCb_MoveToPlayer::CleanUp()
 {
 	if(BotRef)
 	{
 		BotRef->OnReachedDestination.RemoveDynamic(this, &UCb_MoveToPlayer::OnDestinationReached);
 	}
 }
