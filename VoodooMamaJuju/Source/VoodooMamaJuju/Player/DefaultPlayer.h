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

	float cameraDist;
	/*static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialInst(TEXT("/Game/Assets/Materials/Character_Translucent_Mat"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> InvertedMaterialInst(TEXT("/Game/Assets/Materials/InvertedCharacterMaterial"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> greenSolid(TEXT("/Game/Entities/Player/Model/Character_Green_Diffuse"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> greenOutline(TEXT("/Game/Entities/Player/Model/Character_Green_Outline_Diffuse"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> redSolid(TEXT("/Game/Entities/Player/Model/Character_Red_Diffuse"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> redOutline(TEXT("/Game/Entities/Player/Model/Character_Red_Outline_Diffuse"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> purpleSolid(TEXT("/Game/Entities/Player/Model/Character_Purple_Diffuse"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> purpleOutline(TEXT("/Game/Entities/Player/Model/Character_Purple_Outline_Diffuse"));*/
};
