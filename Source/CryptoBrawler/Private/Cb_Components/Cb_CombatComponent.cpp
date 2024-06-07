// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Components/Cb_CombatComponent.h"

#include "FMODBlueprintStatics.h"
#include "PaperZDAnimationComponent.h"
#include "Cb_CombatStateMachine/Cb_CombatState.h"
#include "Cb_CombatStateMachine/Cb_CombatStateMachine.h"
#include "Cb_ToolBox/Cb_CombatEnums.h"
#include "Cb_ToolBox/Cb_LogCategories.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


UCb_CombatComponent::UCb_CombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	AnimationOverrideEndDelegate.BindUObject(this, &UCb_CombatComponent::OnAnimationEnded);

	StartUpperBodyHit = CreateDefaultSubobject<USceneComponent>("Start Upper Body Hit");
	EndUpperBodyHit = CreateDefaultSubobject<USceneComponent>("End Upper Body Hit");

	CurrentSequence = ESequenceName::None;
}

void UCb_CombatComponent::HandlePunch()
{
	if(CurrentState)
	{
		CurrentState->Punch(this);
	}
}

void UCb_CombatComponent::HandleKnockBack()
{
	if(CurrentState)
	{
		CurrentState->KnockBack(this);
	}
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
		if(AnimInstanceRef->PlayAnimationOverride(CombatSequences[SequenceName],
			"DefaultSlot", 1, 0, AnimationOverrideEndDelegate))
		{
			CurrentSequence = SequenceName;
		}
	}
}

void UCb_CombatComponent::ChangeCurrentState(const ECombatState& State)
{
	UE_LOG(LogCbCombat, Display, TEXT("[%s] ChangeCurrentState <%s>"), *GetName(), *UEnum::GetValueAsString(State));
	CurrentState = CombatStateMachine->ChangeState(State);

	if(CurrentState)
	{
		CurrentState->EnterState(this);
	}
}

void UCb_CombatComponent::BeginPlay()
{
	Super::BeginPlay();

	CombatStateMachine = NewObject<UCb_CombatStateMachine>();
	CombatStateMachine->GenerateStates();
	
	CurrentState = CombatStateMachine->ChangeState(ECombatState::Standing);
	
	if(AnimationComponentRef)
	{
		AnimInstanceRef = AnimationComponentRef->GetAnimInstance();
	}

	if(GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UCb_CombatComponent::DamageTaken);
	}
}

void UCb_CombatComponent::OnAnimationEnded(bool Completed)
{
	UE_LOG(LogCb, Display, TEXT("[%s] OnAnimationEnded %d"), *GetName(), Completed);
	
	if(CurrentState)
	{
		CurrentState->SequenceEnded(this, CurrentSequence);
	}

	CurrentSequence = ESequenceName::None;
}

void UCb_CombatComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	if(DamagedActor)
	{
		UE_LOG(LogCb, Display, TEXT("[%s] DamageActor %s"), *GetName(), *DamagedActor->GetName());

		if(HitImpactEvent) // Make this a method the state machine can call
		{
			UFMODBlueprintStatics::PlayEventAtLocation(GetWorld(), HitImpactEvent, GetOwner()->GetActorTransform(), true);
		}

		AddCameraShake(1.f);
		
		HandleKnockBack();
	}
}

void UCb_CombatComponent::AddCameraShake(float Scale)
{
	if(APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0))
	{
		if(*CameraShakeClass)
		{
			CameraManager->StartCameraShake(CameraShakeClass, Scale);
		}
	}
}

