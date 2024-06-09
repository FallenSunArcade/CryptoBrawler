// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_BTServices/Cb_GetPlayerDistance.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


UCb_GetPlayerDistance::UCb_GetPlayerDistance()
{
	NodeName = "Get Player Distance";
}

void UCb_GetPlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControlledPawn)
	{
		return;
	}

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		return;
	}

	float DistanceToPlayer = FVector::Dist(ControlledPawn->GetActorLocation(), PlayerCharacter->GetActorLocation());
	
	if (UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
	{
		BlackboardComp->SetValueAsFloat(GetSelectedBlackboardKey(), DistanceToPlayer);
	}
}
