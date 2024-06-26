﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Cb_MoveToPlayer.generated.h"


class ACb_Bot;
/**
 * This will move the bot class to the player
 */
UCLASS()
class CRYPTOBRAWLER_API UCb_MoveToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UCb_MoveToPlayer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void OnDestinationReached(bool DestinationReached);
	
	void CleanUp();

private:
	UPROPERTY(EditAnywhere)
	float AcceptableDistance = 20.f;

	UPROPERTY(EditAnywhere)
	bool bIsMoveAway = false;

	UPROPERTY(Transient)
	TObjectPtr<UBehaviorTreeComponent> BTComponent;
	
	UPROPERTY(Transient)
	TObjectPtr<ACb_Bot> BotRef;
};
