// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cb_VitalityComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateHealthDelegate, float, Percentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateEnergyDelegate, float, Percentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeadDelegate);


class UCapsuleComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTOBRAWLER_API UCb_VitalityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCb_VitalityComponent();

	void SetCapsuleComponentRef(const TObjectPtr<UCapsuleComponent> CapsuleComponent) { CapsuleComponentRef = CapsuleComponent; }

	void UpdateHealth(float Delta);

	FUpdateHealthDelegate UpdateHealthDelegate;

	FUpdateEnergyDelegate UpdateEnergyDelegate;
	
	FDeadDelegate DeadDelegate;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Transient)
	TObjectPtr<UCapsuleComponent> CapsuleComponentRef;

	UPROPERTY(EditAnywhere, Category = "Vitality")
	float CurrentHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Vitality", meta = (ClampMin = 1.f))
	float MaxHealth = 100.f;
	
	UPROPERTY(EditAnywhere, Category = "Vitality")
	float CurrentEnergy = 100.f;
	
	UPROPERTY(EditAnywhere, Category = "Vitality", meta = (ClampMin = 1.f))
	float MaxEnergy = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAlive = true;
};
