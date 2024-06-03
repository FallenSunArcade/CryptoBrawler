// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cb_FightingCamera.generated.h"


class UCameraComponent;
UCLASS()
class CRYPTOBRAWLER_API ACb_FightingCamera : public AActor
{
	GENERATED_BODY()

public:
	ACb_FightingCamera();

protected:
	virtual void BeginPlay() override;
	
	void SetLocalPlayerViewTarget();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
};
