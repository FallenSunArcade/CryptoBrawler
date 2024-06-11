// Fill out your copyright notice in the Description page of Project Settings.


#include "Cb_Characters/Cb_Player.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PaperFlipbookComponent.h"
#include "Cb_Components/Cb_CombatComponent.h"
#include "Cb_Components/Cb_VitalityComponent.h"
#include "Cb_GameMode/Cb_GameModeBase.h"
#include "Cb_ToolBox/Cb_CombatEnums.h"
#include "GameFramework/CharacterMovementComponent.h"


ACb_Player::ACb_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MaxAcceleration = 300.f;

	CombatComponent = CreateDefaultSubobject<UCb_CombatComponent>(TEXT("Combat Component"));
	CombatComponent->SetAnimationComponentRef(GetAnimationComponent());
	CombatComponent->GetStartUpperHitScene()->SetupAttachment(GetRootComponent());
	CombatComponent->GetEndUpperHitScene()->SetupAttachment(GetRootComponent());
	
	VitalityComponent = CreateDefaultSubobject<UCb_VitalityComponent>("Vitality Component");
	VitalityComponent->SetCapsuleComponentRef(GetCapsuleComponent());

	CombatComponent->SetVitalityRef(VitalityComponent);
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

	if(ACb_GameModeBase* GameMode = Cast<ACb_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->ReadyPlayerOne(this);
	}
}

void ACb_Player::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACb_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACb_Player::BeginJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACb_Player::EndJump);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACb_Player::Move);
		EnhancedInputComponent->BindAction(PunchAction, ETriggerEvent::Triggered, this, &ACb_Player::Punch);
		EnhancedInputComponent->BindAction(KickAction, ETriggerEvent::Triggered, this, &ACb_Player::Kick);
		EnhancedInputComponent->BindAction(StartBlockAction, ETriggerEvent::Triggered, this, &ACb_Player::StartBlock);
		EnhancedInputComponent->BindAction(EndBlockAction, ETriggerEvent::Triggered, this, &ACb_Player::EndBlock);
	}
}

void ACb_Player::Move(const FInputActionValue& Value)
{
	float MovementValue = Value.Get<float>();
	
	if(GetCharacterMovement()->IsFalling() || CombatComponent->GetCurrentCombatMode() == ECombatMode::StandingBlock)
	{
		return;
	}

	if(CombatComponent->GetCurrentSequence() == ESequenceName::None)
	{
		AddMovementInput(GetActorForwardVector(), MovementValue);
	}
	else
	{
		GetController()->StopMovement();
	}

}

void ACb_Player::BeginJump(const FInputActionValue& Value)
{
	// Let State machine handle jumping
	// Can still use Character classes built-in Jumps functions
}

void ACb_Player::EndJump(const FInputActionValue& Value)
{
}

void ACb_Player::Punch(const FInputActionValue& Value)
{
	if(CombatComponent)
	{
		CombatComponent->HandlePunch();
	}
}

void ACb_Player::Kick(const FInputActionValue& Value)
{
	if(CombatComponent)
	{
		CombatComponent->HandleKick();
	}
}

void ACb_Player::StartBlock(const FInputActionValue& Value)
{
	if(CombatComponent)
	{
		CombatComponent->HandleEnterCombatMode(ECombatMode::StandingBlock);
	}
}

void ACb_Player::EndBlock(const FInputActionValue& Value)
{
	if(CombatComponent)
	{
		CombatComponent->HandleEnterCombatMode(ECombatMode::Standing);
	}
}

