// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cb_VitalityComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeadDelegate);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTOBRAWLER_API UCb_VitalityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCb_VitalityComponent();

protected:
	virtual void BeginPlay() override;
};