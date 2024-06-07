﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cb_PlayerCard.generated.h"


class UProgressBar;
/**
 * 
 */
UCLASS()
class CRYPTOBRAWLER_API UCb_PlayerCard : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void UpdateHealth(float Percentage);

	UFUNCTION()
	void UpdateEnergy(float Percentage);

protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> EnergyBar;

	UPROPERTY(EditAnywhere)
	bool bIsPlayerOne = true;
};
