// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Characters/Cb_Bot.h"


// Sets default values
ACb_Bot::ACb_Bot()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACb_Bot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACb_Bot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACb_Bot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

