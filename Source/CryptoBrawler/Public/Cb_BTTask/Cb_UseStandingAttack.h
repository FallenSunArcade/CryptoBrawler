// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Cb_UseStandingAttack.generated.h"

class UCb_CombatComponent;
/**
 * 
 */
UCLASS()
class CRYPTOBRAWLER_API UCb_UseStandingAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UCb_UseStandingAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void OnCombatSequenceEnded();
	
	void CleanUp();

private:
	UPROPERTY(Transient)
	TObjectPtr<UBehaviorTreeComponent> BTComponent;
	
	UPROPERTY(Transient)
	TObjectPtr<UCb_CombatComponent> CombatComponentRef;
};
