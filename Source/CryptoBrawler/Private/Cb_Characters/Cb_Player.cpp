// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Characters/Cb_Player.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"


ACb_Player::ACb_Player()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MaxAcceleration = 300.f;
}

void ACb_Player::AddCameraShake(float Scale)
{
	if(*CameraShakeClass == nullptr)
	{
		return;
	}
	
	if(APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0))
	{
		CameraManager->StartCameraShake(CameraShakeClass, Scale);
	}
}

void ACb_Player::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if(APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0))
	{
		CameraManager->StartCameraFade(1.f, 0.f, 2.f, FLinearColor::Black);
	}
}

void ACb_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACb_Player::Move);
		EnhancedInputComponent->BindAction(PunchAction, ETriggerEvent::Triggered, this, &ACb_Player::Punch);
	}
}

void ACb_Player::Move(const FInputActionValue& Value)
{
	float MovementValue = Value.Get<float>();
	
	if(GetCharacterMovement()->IsFalling())
	{
		return;
	}
	if(MovementValue < 0)
	{
		GetSprite()->SetWorldRotation({0.f, 180.f, 0.f});
		SetActorRotation({0.f, 180.f, 0.f});
	}
	else
	{
		GetSprite()->SetWorldRotation({0.f, 0.f, 0.f});
		SetActorRotation({0.f, 0.f, 0.f});
	}

	float Scale = FMath::Abs(MovementValue);
	AddMovementInput(GetActorForwardVector(), Scale);
}

void ACb_Player::Punch(const FInputActionValue& Value)
{
	if(UPaperZDAnimationComponent* AnimationComponentRef = GetAnimationComponent())
	{
		if( UPaperZDAnimInstance* AnimInstanceRef = AnimationComponentRef->GetAnimInstance())
		{
			if(AnimSequence)
			{
				AnimInstanceRef->PlayAnimationOverride(AnimSequence);
				
			}
		}
	}
}

