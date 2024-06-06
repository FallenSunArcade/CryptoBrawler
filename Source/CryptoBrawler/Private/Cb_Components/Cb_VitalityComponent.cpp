// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Components/Cb_VitalityComponent.h"
#include "Cb_ToolBox/Cb_LogCategories.h"


UCb_VitalityComponent::UCb_VitalityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCb_VitalityComponent::BeginPlay()
{
	Super::BeginPlay();

	if(GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UCb_VitalityComponent::DamageTaken);
	}
}

void UCb_VitalityComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	// I could use the location of the damage with the capsule component to determine if it was an upper/lower body
	// and then pass this to the combat component for blocking
	 
	if(DamagedActor)
	{
		UE_LOG(LogCb, Display, TEXT("[%s] DamageActor %s"), *GetName(), *DamagedActor->GetName());
	}
}