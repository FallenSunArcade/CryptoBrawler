// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Cb_Bot.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReachedDestination, bool, ReachedDestination);

class UCb_CombatComponent;
class UCb_VitalityComponent;
class ACb_BotController;

UCLASS()
class CRYPTOBRAWLER_API ACb_Bot : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ACb_Bot();

	void MoveToPlayer(float Distance);

	void MoveAwayFromPlayer(float Distance);

	FOnReachedDestination OnReachedDestination;
	
protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaSeconds) override;

	void StartMovementTimer();
	
	void HandleMovementTimeout();

	UFUNCTION()
	void HandleDeath();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = _Components)
	TObjectPtr<UCb_CombatComponent> CombatComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = _Components)
	TObjectPtr<UCb_VitalityComponent> VitalityComponent;;

private:
	UPROPERTY(Transient)
	TObjectPtr<APaperZDCharacter> PlayerOneRef;

	UPROPERTY(Transient)
	TObjectPtr<ACb_BotController> BotControllerRef;
	
	FVector TargetLocation;

	float AcceptableDistance  = 20.f;

	float MoveTimeout = 3.f;

	float ScaleValue = 1.f;
	
	FTimerHandle MoveTimeoutHandle;
};
