// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Components/Cb_CombatComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Cb_ToolBox/Cb_CombatEnums.h"
#include "Cb_ToolBox/Cb_LogCategories.h"
#include "Engine/DamageEvents.h"
#include "Kismet/KismetSystemLibrary.h"


UCb_CombatComponent::UCb_CombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	AnimationOverrideEndDelegate.BindUObject(this, &UCb_CombatComponent::OnAnimationEnded);

	StartUpperBodyHit = CreateDefaultSubobject<USceneComponent>("Start Upper Body Hit");
	EndUpperBodyHit = CreateDefaultSubobject<USceneComponent>("End Upper Body Hit");
}

void UCb_CombatComponent::HandlePunch()
{
	PlayCombatSequence(ESequenceName::Punch);
}

void UCb_CombatComponent::HandleKnockBack()
{
}

void UCb_CombatComponent::HandleUpperBodyHitDetection()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	FHitResult BoxHit;

	if (UKismetSystemLibrary::BoxTraceSingle(
		this,
		StartUpperBodyHit->GetComponentLocation(),
		EndUpperBodyHit->GetComponentLocation(),
		FVector(12.f, 8.f, 20.f),
		StartUpperBodyHit->GetComponentRotation(),
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel3),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		BoxHit,
		true
	))
	{
		FPointDamageEvent DamageEvent;
		DamageEvent.Damage = 10.f;
		DamageEvent.HitInfo = BoxHit;

		BoxHit.GetActor()->TakeDamage(10.f, DamageEvent, nullptr, GetOwner());
	}
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

