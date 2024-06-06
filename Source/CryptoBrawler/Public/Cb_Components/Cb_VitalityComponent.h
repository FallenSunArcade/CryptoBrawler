// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cb_VitalityComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeadDelegate);


class UCapsuleComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTOBRAWLER_API UCb_VitalityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCb_VitalityComponent();

	void SetCapsuleComponentRef(const TObjectPtr<UCapsuleComponent> CapsuleComponent) { CapsuleComponentRef = CapsuleComponent; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
		AController* Instigator, AActor* DamageCauser);

	UPROPERTY(Transient)
	TObjectPtr<UCapsuleComponent> CapsuleComponentRef;
};
