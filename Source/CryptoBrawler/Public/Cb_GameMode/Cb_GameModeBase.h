// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Cb_GameModeBase.generated.h"


class UCb_HudOverlay;
class APaperZDCharacter;
/**
 * 
 */
UCLASS()
class CRYPTOBRAWLER_API ACb_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ReadyPlayerOne(const TObjectPtr<APaperZDCharacter> PaperCharacter);
	
	// This is just spawning a bot right now
	void SpawnPlayerTwo();

	TObjectPtr<APaperZDCharacter> GetPlayerTwoRef() const { return PlayerTwoRef; }

	
protected:
	virtual void BeginPlay() override;

	void CreateOverlay();

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UCb_HudOverlay> HudOverlayClass;

	UPROPERTY(Transient)
	TObjectPtr<UCb_HudOverlay> HudOverlayRef;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APaperZDCharacter> BotClass;
	
	UPROPERTY(Transient)
	TObjectPtr<APaperZDCharacter> PlayerOneRef;

	UPROPERTY(Transient)
	TObjectPtr<APaperZDCharacter> PlayerTwoRef;
};
