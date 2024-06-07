// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Components/Cb_VitalityComponent.h"
#include "Cb_ToolBox/Cb_LogCategories.h"


UCb_VitalityComponent::UCb_VitalityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCb_VitalityComponent::UpdateHealth(float Delta)
{
	CurrentHealth -= Delta;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);

	if(CurrentHealth == 0)
	{
		DeadDelegate.Broadcast();
		bIsAlive = false;
	}

	UpdateHealthDelegate.Broadcast(CurrentHealth / MaxHealth);
	
}

void UCb_VitalityComponent::BeginPlay()
{
	Super::BeginPlay();


}
