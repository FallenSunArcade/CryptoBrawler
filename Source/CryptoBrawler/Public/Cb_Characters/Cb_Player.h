// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Cb_Player.generated.h"


class UInputComponent;
struct FInputActionValue;
class UCameraShakeBase;
class UPaperZDAnimSequence;
class UCb_CombatComponent;
class UCb_VitalityComponent;


UCLASS()
class CRYPTOBRAWLER_API ACb_Player : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ACb_Player();

	UFUNCTION(BlueprintCallable)
	void AddCameraShake(float Scale);
	
protected:
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void Move(const FInputActionValue& Value);

	void Punch(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CameraShakeClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PunchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = _Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCb_CombatComponent> CombatComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = _Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCb_VitalityComponent> VitalityComponent;

	UPROPERTY(EditAnywhere)
	UPaperZDAnimSequence* AnimSequence;
};
