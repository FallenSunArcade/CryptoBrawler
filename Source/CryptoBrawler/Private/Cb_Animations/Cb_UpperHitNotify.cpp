// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Animations/Cb_UpperHitNotify.h"

#include "PaperZDAnimInstance.h"
#include "Cb_Components/Cb_CombatComponent.h"

void UCb_UpperHitNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if(GWorld->HasBegunPlay())
	{
		if(AActor* Owner = OwningInstance->GetOwningActor())
		{
			if(UCb_CombatComponent* CombatComponent = Owner->GetComponentByClass<UCb_CombatComponent>())
			{
				CombatComponent->HandleUpperBodyHitDetection();
			}
		}
	}
}
