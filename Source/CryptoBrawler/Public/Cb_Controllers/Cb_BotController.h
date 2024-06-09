// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIModule/Classes/AIController.h"
#include "Cb_BotController.generated.h"


UENUM(BlueprintType)
enum class EBotState : uint8
{
	Defending,
	Attacking
 };

class UBehaviorTree;

UCLASS()
class CRYPTOBRAWLER_API ACb_BotController : public AAIController
{
	GENERATED_BODY()

public:
	ACb_BotController();

	void SetBotState(const EBotState& State);

protected:
	virtual void BeginPlay() override;

	void HandleSwitchState();

	void GenerateRandomSwitchTimer();
	
private:
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	TObjectPtr<UBehaviorTree> CurrentBehaviorTree;

	FTimerHandle RandomSwitchStateHandle;

	EBotState CurrentState;
};

