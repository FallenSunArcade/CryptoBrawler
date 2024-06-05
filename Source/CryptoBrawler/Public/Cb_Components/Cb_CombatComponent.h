// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cb_CombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTOBRAWLER_API UCb_CombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCb_CombatComponent();

protected:
	virtual void BeginPlay() override;
};
