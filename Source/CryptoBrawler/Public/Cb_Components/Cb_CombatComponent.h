// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "Components/ActorComponent.h"
#include "Cb_CombatComponent.generated.h"

enum class ESequenceName : uint8;
class UPaperZDAnimationComponent;
class UPaperZDAnimInstance;
class UCb_CombatStateMachine;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTOBRAWLER_API UCb_CombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCb_CombatComponent();

	void SetAnimationComponentRef(UPaperZDAnimationComponent* AnimationComponent) { AnimationComponentRef = AnimationComponent; };

	void HandlePunch();

	void HandleKnockBack();

	void PlayCombatSequence(const ESequenceName& SequenceName);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnAnimationEnded(bool Completed);

	UPROPERTY(EditAnywhere)
	TMap<ESequenceName, UPaperZDAnimSequence*> CombatSequences;

	UPROPERTY(Transient)
	TObjectPtr<UPaperZDAnimationComponent> AnimationComponentRef;
	
	UPROPERTY(Transient)
	TObjectPtr<UPaperZDAnimInstance> AnimInstanceRef;

	FZDOnAnimationOverrideEndSignature AnimationOverrideEndDelegate;
};
