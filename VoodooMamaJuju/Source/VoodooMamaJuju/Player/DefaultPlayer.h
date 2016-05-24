// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Player/PlayerBase.h"
#include "DefaultPlayer.generated.h"

/**
 * 
 */
UCLASS()
class VOODOOMAMAJUJU_API ADefaultPlayer : public APlayerBase
{
	GENERATED_BODY()

	//TODO: Maybe find a more logical place for the camera logic? (just copied from TP_ThirdPersonCharacter.H example)

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Effects, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent *PlayerSpark;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Effects, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent *PlayerBuff;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Effects, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent *PlayerDebuff;

public:
	ADefaultPlayer();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Camera shake stuffies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
	TSubclassOf<UCameraShake> landingShake;

	void Tick(float DeltaSeconds) override;
	void MoveForward(float value) override;
	void Lookup(float value) override;
	void BuffPlayer() override;
	void DebuffPlayer() override;
	void RemoveBuff() override;
	void RemoveDebuff() override;
	void Buff() override;
	void Debuff() override;
	void SetLastingBuff() override;
	void SetLastingDebuff() override;
	void NormalColor() override;
	void BuffColor() override;
	void DebuffColor() override;
	void NormalMovement() override;
	void TimelineFinished() override;
	void TimelinePullBack() override;
	void FadePlayer() override;
	void StopFade() override;
	void FadeUpdate() override;
	void FadeFinished() override;

	float cameraDist;

	UFUNCTION(BlueprintImplementableEvent, Category = "Matinee")
	void PlayMatinee();

	UFUNCTION(BluePrintCallable, Category = "CameraEffects")
	void PlayShake();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sounds")
	void PlayMoving();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sounds")
	void StopMoving();
	
	UFUNCTION(BluePrintCallable, Category = "Sounds")
	void Squish();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sounds")
	void PlaySquish();
};