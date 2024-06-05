// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Components/Cb_CombatComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Cb_ToolBox/Cb_CombatEnums.h"
#include "Cb_ToolBox/Cb_LogCategories.h"


UCb_CombatComponent::UCb_CombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	AnimationOverrideEndDelegate.BindUObject(this, &UCb_CombatComponent::OnAnimationEnded);
}

void UCb_CombatComponent::HandlePunch()
{
	PlayCombatSequence(ESequenceName::Punch);
}

void UCb_CombatComponent::HandleKnockBack()
{
}

void UCb_CombatComponent::PlayCombatSequence(const ESequenceName& SequenceName)
{
	if(!AnimInstanceRef)
	{
		UE_LOG(LogCb, Error, TEXT("[%s] AnimInstanceRef is invalid"), *GetName());
		return;
	}

	UE_LOG(LogCb, Display, TEXT("[%s] PlayCombatSequence %s"), *GetName(), *UEnum::GetValueAsString(SequenceName));
	
	if(CombatSequences.Find(SequenceName))
	{
		AnimInstanceRef->PlayAnimationOverride(CombatSequences[SequenceName],
			"DefaultSlot", 1, 0, AnimationOverrideEndDelegate);
	}
}

void UCb_CombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if(AnimationComponentRef)
	{
		AnimInstanceRef = AnimationComponentRef->GetAnimInstance();
	}
}

void UCb_CombatComponent::OnAnimationEnded(bool Completed)
{
	UE_LOG(LogCb, Display, TEXT("[%s] OnAnimationEnded %d"), *GetName(), Completed);
}

