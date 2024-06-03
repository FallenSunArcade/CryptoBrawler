// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Controllers/Cb_PlayerController.h"
#include "Cb_Cameras/Cb_FightingCamera.h"
#include "Cb_ToolBox/Cb_LogCategories.h"
#include "Cb_UI/Cb_HudOverlay.h"


void ACb_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(IsLocalController())
	{
		CreateOverlay();
	}
}

void ACb_PlayerController::CreateOverlay()
{
	if (*HudOverlayClass)
	{
		HudOverlayRef = CreateWidget<UCb_HudOverlay>(this, HudOverlayClass);

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
