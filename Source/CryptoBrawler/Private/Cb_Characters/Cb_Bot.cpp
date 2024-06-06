// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Characters/Cb_Bot.h"
#include "Cb_Components/Cb_CombatComponent.h"
#include "Cb_Components/Cb_VitalityComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ACb_Bot::ACb_Bot()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MaxAcceleration = 300.f;

	CombatComponent = CreateDefaultSubobject<UCb_CombatComponent>(TEXT("Combat Component"));
	CombatComponent->SetAnimationComponentRef(GetAnimationComponent());

	VitalityComponent = CreateDefaultSubobject<UCb_VitalityComponent>("Vitality Component");
	VitalityComponent->SetCapsuleComponentRef(GetCapsuleComponent());
	
}

void ACb_Bot::BeginPlay()
{
	Super::BeginPlay();
	
}
