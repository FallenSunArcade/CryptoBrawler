// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Cameras/Cb_FightingCamera.h"
#include "Camera/CameraComponent.h"


ACb_FightingCamera::ACb_FightingCamera()
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SetRootComponent(CameraComponent);

	bReplicates = true;
}

void ACb_FightingCamera::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		SetLocalPlayerViewTarget();
	}
}

void ACb_FightingCamera::SetLocalPlayerViewTarget()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Iterator->Get();
		if (PC && PC->IsLocalController())
		{
			PC->SetViewTarget(this);
		}
	}
}

