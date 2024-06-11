// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "Cb_ToolBox/Cb_CombatEnums.h"
#include "Components/ActorComponent.h"
#include "Cb_CombatComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatMontageEnded);

class UCb_VitalityComponent;
class UPaperZDAnimationComponent;
class UPaperZDAnimInstance;
class UCb_CombatStateMachine;
class UCb_CombatState;
class UFMODEvent;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTOBRAWLER_API UCb_CombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCb_CombatComponent();

	void SetAnimationComponentRef(UPaperZDAnimationComponent* AnimationComponent) { AnimationComponentRef = AnimationComponent; }

	void SetVitalityRef(UCb_VitalityComponent* VitalityComponent) { VitalityComponentRef = VitalityComponent; }
	
	void HandlePunch();

	void HandleKick();

	void HandleKnockBack();	

	void HandleUpperBodyHitDetection();

	void HandleEnterCombatMode(const ECombatMode& CombatMode);

	void PlayCombatSequence(const ESequenceName& SequenceName);

	void ChangeCurrentState(const ECombatState& State);

	TObjectPtr<USceneComponent> GetStartUpperHitScene() const { return StartUpperBodyHit; }

	TObjectPtr<USceneComponent> GetEndUpperHitScene() const { return EndUpperBodyHit; }
	
	ESequenceName GetCurrentSequence() const { return CurrentSequence; }

	void SetCurrentCombatMode(const ECombatMode& CombatMode) { CurrentMode = CombatMode; }

	ECombatMode GetCurrentCombatMode() const { return CurrentMode; }

	FOnCombatMontageEnded OnCombatMontageEnded;

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION()
	void OnAnimationEnded(bool Completed);

	UFUNCTION()
	virtual void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
		AController* Instigator, AActor* DamageCauser);
	
	void AddCameraShake(float Scale);

	UPROPERTY(EditAnywhere)
	TMap<ESequenceName, UPaperZDAnimSequence*> CombatSequences;

	UPROPERTY(Transient)
	TObjectPtr<UCb_VitalityComponent> VitalityComponentRef;

	UPROPERTY(Transient)
	TObjectPtr<UPaperZDAnimationComponent> AnimationComponentRef;
	
	UPROPERTY(Transient)
	TObjectPtr<UPaperZDAnimInstance> AnimInstanceRef;

	FZDOnAnimationOverrideEndSignature AnimationOverrideEndDelegate;

	UPROPERTY(EditAnywhere, Category = "Hit Impact")
	TObjectPtr<USceneComponent> StartUpperBodyHit;
	
	UPROPERTY(EditAnywhere, Category = "Hit Impact")
	TObjectPtr<USceneComponent> EndUpperBodyHit;

	UPROPERTY(EditAnywhere, Category = "Hit Impact")
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

	UPROPERTY(EditAnywhere, Category = "Hit Impact", BlueprintReadWrite)
	TObjectPtr<UFMODEvent> HitImpactEvent;
	
	UPROPERTY(EditAnywhere, Category = "Hit Impact", BlueprintReadWrite)
	TObjectPtr<UFMODEvent> BlockImpactEvent;

	UPROPERTY(Transient)
	TObjectPtr<UCb_CombatStateMachine> CombatStateMachine;

	UPROPERTY(Transient)
	TObjectPtr<UCb_CombatState> CurrentState;

	ESequenceName CurrentSequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECombatMode CurrentMode;
};
