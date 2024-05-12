// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Characters/Cb_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


class UEnhancedInputLocalPlayerSubsystem;

ACb_Player::ACb_Player()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MaxAcceleration = 300.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->SetWorldRotation({0.f, -90.f, 0.f});
	CameraBoom->bUsePawnControlRotation = true; 
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
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

