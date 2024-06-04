// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotify.h"
#include "Cb_PlayFmodSound.generated.h"


class UFMODEvent;
/**
 * 
 */
UCLASS()
class CRYPTOBRAWLER_API UCb_PlayFmodSound : public UPaperZDAnimNotify
{
	GENERATED_BODY()

public:
	void OnReceiveNotify_Implementation(UPaperZDAnimInstance *OwningInstance = nullptr) const override;
	
	FName GetDisplayName_Implementation() const override;
	
	UPROPERTY(EditAnywhere, Category = "FMOD Anim Notify", BlueprintReadWrite)
	TObjectPtr<UFMODEvent> Event;
};
