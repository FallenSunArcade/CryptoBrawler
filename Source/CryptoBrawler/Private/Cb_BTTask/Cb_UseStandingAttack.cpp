// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_BTTask/Cb_UseStandingAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Cb_Characters/Cb_Bot.h"
#include "Cb_Components/Cb_CombatComponent.h"
#include "Cb_ToolBox/Cb_LogCategories.h"


class ACb_Bot;

UCb_UseStandingAttack::UCb_UseStandingAttack()
{
	NodeName = TEXT("Use Standing Attack");
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UCb_UseStandingAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	BTComponent = OwnerComp;
 	
	const AAIController* AIController = OwnerComp.GetAIOwner();
 	
	if (!AIController)
	{
		UE_LOG(LogCbAI, Warning, TEXT("[%s] AIController is %p"), *GetName(), AIController);
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	if(ACb_Bot* BotRef = Cast<ACb_Bot>(AIController->GetPawn()))
	{
		CombatComponentRef = BotRef->GetComponentByClass<UCb_CombatComponent>();

		if(CombatComponentRef)
		{
			if(CombatComponentRef->GetCurrentSequence() == ESequenceName::None)
			{
				float DistanceToPlayer = BlackboardComp->GetValueAsFloat(GetSelectedBlackboardKey());

				if(DistanceToPlayer < 160.f)
				{
					CombatComponentRef->HandlePunch();
					CombatComponentRef->OnCombatMontageEnded.AddDynamic(this, &UCb_UseStandingAttack::OnCombatSequenceEnded);
					return EBTNodeResult::InProgress;
				}
			}
		}

	}

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UCb_UseStandingAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CleanUp();
	return EBTNodeResult::Aborted;
}

void UCb_UseStandingAttack::OnCombatSequenceEnded()
{
	if (BTComponent)
	{
		UE_LOG(LogCbAI, Display, TEXT("[%s] OnCombatSequenceEnded"), *GetName());
		CleanUp();
		FinishLatentTask(*BTComponent, EBTNodeResult::Succeeded);
	}
}

void UCb_UseStandingAttack::CleanUp()
{
	if(CombatComponentRef)
	{
		CombatComponentRef->OnCombatMontageEnded.RemoveDynamic(this, &UCb_UseStandingAttack::OnCombatSequenceEnded);
	}
}
