// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Cb_CombatStateMachine.generated.h"


enum class ECombatState : uint8;
class UCb_CombatState;
/**
 * 
 */
UCLASS()
class CRYPTOBRAWLER_API UCb_CombatStateMachine : public UObject
{
	GENERATED_BODY()

public:
	void GenerateStates();

	TObjectPtr<UCb_CombatState> ChangeState(const ECombatState& State);

private:
	UPROPERTY(Transient)
	TMap<ECombatState, TObjectPtr<UCb_CombatState>> StateMap;
};
