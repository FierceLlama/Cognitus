// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerMovementComponent.h"
#include "PlayerBase.generated.h"

UCLASS(abstract)
class VOODOOMAMAJUJU_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

private:
	

protected:
	

public:
	// Sets default values for this character's properties
	APlayerBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	//floats and bools for our character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float normalAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float buffAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float debuffAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float normalBrakingDeceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float buffBrakingDeceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float debuffBrakingDeceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool isBuffed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool isDebuffed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool inBuffZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	bool inDebuffZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float normalBoomLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float buffBoomLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float debuffBoomLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float pitchDownAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float pitchUpAngle;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	USkeletalMeshComponent *invertedMesh;*/

	//** Materials */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UMaterialInstanceDynamic *DynamicMatInst;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	//UMaterialInstanceDynamic *InvertedDynamicMatInst;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UTexture2D *solidGreen;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UTexture2D *outlineGreen;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UTexture2D *solidRed;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UTexture2D *outlineRed;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UTexture2D *solidPurple;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UTexture2D *outlinePurple;

	//buff and debuff functions
	UFUNCTION()
	virtual void NormalMovement() PURE_VIRTUAL(APlayerBase::NormalMovement, ;);

	UFUNCTION()
	virtual void BuffPlayer() PURE_VIRTUAL(APlayerBase::BuffPlayer, ;);

	UFUNCTION()
	virtual void DebuffPlayer() PURE_VIRTUAL(APlayerBase::DebuffPlayer, ;);

	UFUNCTION()
	virtual void RemoveBuff() PURE_VIRTUAL(APlayerBase::RemoveBuff, ;);

	UFUNCTION()
	virtual void RemoveDebuff() PURE_VIRTUAL(APlayerBase::RemoveDebuff, ;);

	UFUNCTION()
	virtual void Buff()PURE_VIRTUAL(APlayerBase::Buff, ;);

	UFUNCTION()
	virtual void Debuff() PURE_VIRTUAL(APlayerBase::Debuff, ;);

	UFUNCTION()
	virtual void SetLastingBuff() PURE_VIRTUAL(APlayerBase::SetLastingBuff, ;);

	UFUNCTION()
	virtual void SetLastingDebuff() PURE_VIRTUAL(APlayerBase::SetLastingDebuff, ;);

	/** Color Functions*/
	UFUNCTION()
	virtual void NormalColor() PURE_VIRTUAL(APlayerBase::NormalColor, ;);

	UFUNCTION()
	virtual void BuffColor() PURE_VIRTUAL(APlayerBase::BuffColor, ;);

	UFUNCTION()
	virtual void DebuffColor() PURE_VIRTUAL(APlayerBase::DebuffColor, ;);

	//**Setup Timeline Properties*/
	UPROPERTY(EditAnywhere)
	UTimelineComponent* BuffTimeline;

	UPROPERTY(EditAnywhere)
	UTimelineComponent* PullBackTimeline;

	UPROPERTY(EditAnywhere)
	UTimelineComponent *pFade;

	UFUNCTION()
	virtual void TimelineFinished() PURE_VIRTUAL(APlayerBase::TimelineFinished, ;);

	UFUNCTION()
	virtual void TimelinePullBack() PURE_VIRTUAL(APlayerBase::TimelinePullBack, ;);

	FOnTimelineEvent FinishedFunction{};
	FOnTimelineEvent PullBackFunction{};

	virtual void MoveForward(float value) PURE_VIRTUAL(APlayerBase::MoveForward, ;);
	virtual void Lookup(float value) PURE_VIRTUAL(APlayerBase::Lookup, ;);

	UFUNCTION(BlueprintCallable, Category = PlayerEffects)
	virtual void FadePlayer() PURE_VIRTUAL(APlayerBase::FadePlayer, ;);

	UFUNCTION(BlueprintCallable, Category = PlayerEffects)
	virtual void StopFade() PURE_VIRTUAL(APlayerBase::StopFade, ;);

	UFUNCTION()
	virtual void FadeUpdate() PURE_VIRTUAL(APlayerBase::FadeUpdate, ;);
	FOnTimelineEvent FadeUpdateFunction{};

	UFUNCTION()
	virtual void FadeFinished() PURE_VIRTUAL(APlayerBase::FadeFinished, ;);
	FOnTimelineEvent FadeFinishedFunction{};
};
