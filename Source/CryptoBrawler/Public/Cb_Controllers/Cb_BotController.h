// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIModule/Classes/AIController.h"
#include "Cb_BotController.generated.h"


class UBehaviorTree;
UCLASS()
class CRYPTOBRAWLER_API ACb_BotController : public AAIController
{
	GENERATED_BODY()

public:
	ACb_BotController();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	TObjectPtr<UBehaviorTree> CurrentBehaviorTree;
};
