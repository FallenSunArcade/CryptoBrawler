// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Cb_Bot.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReachedPlayer);

class UCb_CombatComponent;
class UCb_VitalityComponent;

UCLASS()
class CRYPTOBRAWLER_API ACb_Bot : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ACb_Bot();

	void MoveToPlayer(float Distance);

	FOnReachedPlayer OnReachedPlayer;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = _Components)
	TObjectPtr<UCb_CombatComponent> CombatComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = _Components)
	TObjectPtr<UCb_VitalityComponent> VitalityComponent;;

private:
	UPROPERTY(Transient)
	TObjectPtr<APaperZDCharacter> PlayerOneRef;
	
	FVector TargetLocation;

	float AcceptableDistance  = 20.f;
	
	bool bIsMoving;
};
