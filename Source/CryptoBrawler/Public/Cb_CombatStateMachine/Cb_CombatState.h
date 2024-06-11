// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Cb_CombatState.generated.h"


enum class ECombatMode : uint8;
enum class ESequenceName : uint8;
class UCb_CombatComponent;
/**
 * 
 */
UCLASS()
class CRYPTOBRAWLER_API UCb_CombatState : public UObject
{
	GENERATED_BODY()

public:
	virtual void EnterState(TObjectPtr<UCb_CombatComponent> CombatComponent);

	virtual void ExitState(TObjectPtr<UCb_CombatComponent> CombatComponent);

	virtual void SequenceEnded(TObjectPtr<UCb_CombatComponent> CombatComponent, const ESequenceName& SequenceName);

	virtual void Punch(TObjectPtr<UCb_CombatComponent> CombatComponent);
	
	virtual void Kick(TObjectPtr<UCb_CombatComponent> CombatComponent);

	virtual void KnockBack(TObjectPtr<UCb_CombatComponent> CombatComponent);

	virtual void EnterCombatMode(TObjectPtr<UCb_CombatComponent> CombatComponent, const ECombatMode& CombatMode);

	virtual bool CanMove();
};


