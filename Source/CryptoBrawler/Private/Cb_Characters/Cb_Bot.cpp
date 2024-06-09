// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Characters/Cb_Bot.h"

#include "BrainComponent.h"
#include "Cb_Components/Cb_CombatComponent.h"
#include "Cb_Components/Cb_VitalityComponent.h"
#include "Cb_Controllers/Cb_BotController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ACb_Bot::ACb_Bot()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MaxAcceleration = 300.f;

	CombatComponent = CreateDefaultSubobject<UCb_CombatComponent>(TEXT("Combat Component"));
	CombatComponent->SetAnimationComponentRef(GetAnimationComponent());
	CombatComponent->GetStartUpperHitScene()->SetupAttachment(GetRootComponent());
	CombatComponent->GetEndUpperHitScene()->SetupAttachment(GetRootComponent());

	VitalityComponent = CreateDefaultSubobject<UCb_VitalityComponent>("Vitality Component");
	VitalityComponent->SetCapsuleComponentRef(GetCapsuleComponent());

	CombatComponent->SetVitalityRef(VitalityComponent);
}

void ACb_Bot::MoveToPlayer(float Distance)
{
	AcceptableDistance = Distance;
	ScaleValue = 1.f;
	SetActorTickEnabled(true);
	StartMovementTimer();
}

void ACb_Bot::MoveAwayFromPlayer(float Distance)
{
	AcceptableDistance = Distance;
	ScaleValue = -1.f;
	SetActorTickEnabled(true);
	StartMovementTimer();
}

void ACb_Bot::BeginPlay()
{
	Super::BeginPlay();

	PlayerOneRef = Cast<APaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	VitalityComponent->DeadDelegate.AddDynamic(this, &ACb_Bot::HandleDeath);
}

void ACb_Bot::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(HasAuthority())
	{
		BotControllerRef = Cast<ACb_BotController>(NewController);
	}
}

void ACb_Bot::HandleDeath()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorTickEnabled(false);
	GetCharacterMovement()->StopActiveMovement();
	if(BotControllerRef)
	{
		BotControllerRef->BrainComponent->StopLogic("Dead");
	}
}

void ACb_Bot::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerOneRef)
	{
		FVector MyLocation = GetActorLocation();
		FVector PlayerLocation = PlayerOneRef->GetActorLocation();
		
		float Distance = FMath::Abs(PlayerLocation.X - MyLocation.X);

		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red,
		FString::Printf(TEXT("Distance = %f AcceptableDistance = %f"), Distance, AcceptableDistance));

		bool NeedsToMove = true;
		
		if(ScaleValue > 0)
		{
			NeedsToMove = Distance > AcceptableDistance;
		}
		else
		{
			NeedsToMove = Distance < AcceptableDistance;
		}
		
		if (NeedsToMove)
		{
			AddMovementInput(GetActorForwardVector(), ScaleValue);
		}
		else
		{
			SetActorTickEnabled(false);
			OnReachedDestination.Broadcast(true);
			GetWorldTimerManager().ClearTimer(MoveTimeoutHandle);
		}
	}
}

void ACb_Bot::StartMovementTimer()
{
	GetWorldTimerManager().SetTimer(
		MoveTimeoutHandle,
		this,
		&ACb_Bot::HandleMovementTimeout,
		MoveTimeout
		);
}

void ACb_Bot::HandleMovementTimeout()
{
	SetActorTickEnabled(false);
	OnReachedDestination.Broadcast(false);
}
