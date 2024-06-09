// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Cb_GetPlayerDistance.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTOBRAWLER_API UCb_GetPlayerDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UCb_GetPlayerDistance();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
