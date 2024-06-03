// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Cb_PlayerController.generated.h"


class UCb_HudOverlay;
/**
 * 
 */
UCLASS()
class CRYPTOBRAWLER_API ACb_PlayerController : public APlayerController
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
