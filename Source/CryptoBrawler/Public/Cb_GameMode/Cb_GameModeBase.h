// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Cb_GameModeBase.generated.h"


class UCb_HudOverlay;
/**
 * 
 */
UCLASS()
class CRYPTOBRAWLER_API ACb_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void CreateOverlay();

private:
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UCb_HudOverlay> HudOverlayClass;

	UPROPERTY(Transient)
	TObjectPtr<UCb_HudOverlay> HudOverlayRef;
	
};
