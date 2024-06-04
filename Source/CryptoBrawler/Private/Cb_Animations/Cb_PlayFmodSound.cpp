// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Animations/Cb_PlayFmodSound.h"
#include "FMODBlueprintStatics.h"


void UCb_PlayFmodSound::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	UFMODBlueprintStatics::PlayEventAtLocation(GetWorld(), Event, SequenceRenderComponent->GetComponentTransform(), true);
}

FName UCb_PlayFmodSound::GetDisplayName_Implementation() const
{
	return Super::GetDisplayName_Implementation();
}
