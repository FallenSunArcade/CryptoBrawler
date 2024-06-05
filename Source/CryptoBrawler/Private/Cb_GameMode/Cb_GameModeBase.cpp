// Fill out your copyright notice in the Description page of Project Settings.
#include "Cb_GameMode/Cb_GameModeBase.h"
#include "Cb_ToolBox/Cb_LogCategories.h"
#include "Cb_UI/Cb_HudOverlay.h"


void ACb_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	CreateOverlay();
}

void ACb_GameModeBase::CreateOverlay()
{
	if (*HudOverlayClass)
	{
		HudOverlayRef = CreateWidget<UCb_HudOverlay>(GetWorld(), HudOverlayClass);

		if(HudOverlayRef)
		{
			HudOverlayRef->AddToViewport();
		}
	}
	else
	{
		UE_LOG(LogCb, Error, TEXT("[%s] HudOverlayClass not set"), *GetName());
	}
}

AActor* ACb_GameModeBase::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	return Super::FindPlayerStart_Implementation(Player, "PlayerOne");
}
