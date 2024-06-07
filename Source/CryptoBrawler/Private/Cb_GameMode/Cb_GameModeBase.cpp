// Fill out your copyright notice in the Description page of Project Settings.
#include "Cb_GameMode/Cb_GameModeBase.h"
#include "EngineUtils.h"
#include "PaperFlipbookComponent.h"
#include "Cb_Characters/Cb_Bot.h"
#include "Cb_ToolBox/Cb_LogCategories.h"
#include "Cb_UI/Cb_HudOverlay.h"
#include "GameFramework/PlayerStart.h"


void ACb_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CreateOverlay();
	SpawnPlayerTwo();
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

void ACb_GameModeBase::ReadyPlayerOne(const TObjectPtr<APaperZDCharacter> PaperCharacter)
{
	if (const AActor* PlayerSpawnPoint = FindPlayerStart(PaperCharacter->GetController(), "PlayerOne"))
	{
		PlayerOneRef = PaperCharacter;

		if(PlayerOneRef)
		{
			PlayerOneRef->SetActorTransform(PlayerSpawnPoint->GetActorTransform());
		}
	}
}

void ACb_GameModeBase::SpawnPlayerTwo()
{
	if(*BotClass == nullptr)
	{
		return;
	}

	PlayerTwoRef = GetWorld()->SpawnActor<APaperZDCharacter>(BotClass);

	if(PlayerTwoRef)
	{
		if (AActor* BotSpawnPoint = FindPlayerStart(PlayerTwoRef->GetController(), "PlayerTwo"))
		{
			PlayerTwoRef->SetActorTransform(BotSpawnPoint->GetActorTransform());
		}
	}
}

AActor* ACb_GameModeBase::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* PlayerStart = *It;
		
		if (PlayerStart && PlayerStart->PlayerStartTag == IncomingName)
		{
			return PlayerStart;
		}
	}

	return Super::FindPlayerStart_Implementation(Player, IncomingName);
}