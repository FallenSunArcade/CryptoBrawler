// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotify.h"
#include "Cb_UpperHitNotify.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTOBRAWLER_API UCb_UpperHitNotify : public UPaperZDAnimNotify
{
	GENERATED_BODY()
	
public:
	void OnReceiveNotify_Implementation(UPaperZDAnimInstance *OwningInstance = nullptr) const override;
};
