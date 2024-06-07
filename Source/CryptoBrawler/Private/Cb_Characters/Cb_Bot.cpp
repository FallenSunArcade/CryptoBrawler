// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Characters/Cb_Bot.h"
#include "Cb_Components/Cb_CombatComponent.h"
#include "Cb_Components/Cb_VitalityComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ACb_Bot::ACb_Bot()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MaxAcceleration = 300.f;

	CombatComponent = CreateDefaultSubobject<UCb_CombatComponent>(TEXT("Combat Component"));
	CombatComponent->SetAnimationComponentRef(GetAnimationComponent());

	VitalityComponent = CreateDefaultSubobject<UCb_VitalityComponent>("Vitality Component");
	VitalityComponent->SetCapsuleComponentRef(GetCapsuleComponent());

	CombatComponent->SetVitalityRef(VitalityComponent);
}

void ACb_Bot::MoveToPlayer(float Distance)
{
	AcceptableDistance = Distance;
	bIsMoving = true;
}

void ACb_Bot::BeginPlay()
{
	Super::BeginPlay();

	PlayerOneRef = Cast<APaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		
}

void ACb_Bot::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsMoving && PlayerOneRef)
	{
		FVector MyLocation = GetActorLocation();
		FVector PlayerLocation = PlayerOneRef->GetActorLocation();

		// Only consider the X-axis for movement
		float Distance = FMath::Abs(PlayerLocation.X - MyLocation.X);

		// GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red,
		// 	FString::Printf(TEXT("Distance = %f bIsMoving = %d"), Distance, bIsMoving));
		if (Distance > AcceptableDistance)
		{
			AddMovementInput(GetActorForwardVector(), 1.f);
		}
		else
		{
			bIsMoving = false;
		}
	}
}
