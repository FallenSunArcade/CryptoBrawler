// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Cb_Bot.generated.h"


class UCb_CombatComponent;
class UCb_VitalityComponent;

UCLASS()
class CRYPTOBRAWLER_API ACb_Bot : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ACb_Bot();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = _Components)
	TObjectPtr<UCb_CombatComponent> CombatComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = _Components)
	TObjectPtr<UCb_VitalityComponent> VitalityComponent;;
};
