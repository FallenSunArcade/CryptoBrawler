// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Components/Cb_CombatComponent.h"


UCb_CombatComponent::UCb_CombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCb_CombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

