// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_UI/Cb_PlayerCard.h"
#include "PaperZDCharacter.h"
#include "Cb_Components/Cb_VitalityComponent.h"
#include "Cb_GameMode/Cb_GameModeBase.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"


void UCb_PlayerCard::UpdateHealth(float Percentage)
{
	if(HealthBar)
	{
		HealthBar->SetPercent(Percentage);
	}
}

void UCb_PlayerCard::UpdateEnergy(float Percentage)
{
	if(EnergyBar)
	{
		EnergyBar->SetPercent(Percentage);
	}
}

void UCb_PlayerCard::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FTimerHandle DelayHandle;
	
	ACb_GameModeBase* GameModeRef = Cast<ACb_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	GetWorld()->GetTimerManager().SetTimer(DelayHandle, [this, GameModeRef]()
	{
		if(GameModeRef)
		{
			if(bIsPlayerOne)
			{
				if(APaperZDCharacter* PlayerOne = GameModeRef->GetPlayerOneRef())
				{
					if(UCb_VitalityComponent* VitalityComponent = PlayerOne->GetComponentByClass<UCb_VitalityComponent>())
					{
						VitalityComponent->UpdateHealthDelegate.AddDynamic(this, &UCb_PlayerCard::UpdateHealth);
					}
				}
			}
			else
			{
				if(APaperZDCharacter* PlayerTwo = GameModeRef->GetPlayerTwoRef())
				{
					if(UCb_VitalityComponent* VitalityComponent = PlayerTwo->GetComponentByClass<UCb_VitalityComponent>())
					{
						VitalityComponent->UpdateHealthDelegate.AddDynamic(this, &UCb_PlayerCard::UpdateHealth);
					}
				}
			}
		}
	}, 0.2f, false);
}
