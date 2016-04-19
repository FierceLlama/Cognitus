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
	UPROPERTY(EditAnywhere)
	float normalAcceleration;

	UPROPERTY(EditAnywhere)
	float buffAcceleration;

	UPROPERTY(EditAnywhere)
	float debuffAcceleration;

	UPROPERTY(EditAnywhere)
	float normalBrakingDeceleration;

	UPROPERTY(EditAnywhere)
	float buffBrakingDeceleration;

	UPROPERTY(EditAnywhere)
	float debuffBrakingDeceleration;

	UPROPERTY(EditAnywhere)
	bool isBuffed;

	UPROPERTY(EditAnywhere)
	bool isDebuffed;

	UPROPERTY(EditAnywhere)
	bool inBuffZone;

	UPROPERTY(EditAnywhere)
	bool inDebuffZone;

	UPROPERTY(EditAnywhere)
	float normalBoomLength;

	UPROPERTY(EditAnywhere)
	float buffBoomLength;

	UPROPERTY(EditAnywhere)
	float debuffBoomLength;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent *invertedMesh;

	//** Materials */
	UPROPERTY()
	UMaterialInstanceDynamic *DynamicMatInst;

	UPROPERTY()
	UMaterialInstanceDynamic *InvertedDynamicMatInst;

	UPROPERTY()
	UTexture2D *solidGreen;

	UPROPERTY()
	UTexture2D *outlineGreen;

	UPROPERTY()
	UTexture2D *solidRed;

	UPROPERTY()
	UTexture2D *outlineRed;

	UPROPERTY()
	UTexture2D *solidPurple;

	UPROPERTY()
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

	UFUNCTION()
	virtual void TimelineFinished() PURE_VIRTUAL(APlayerBase::TimelineFinished, ;);

	UFUNCTION()
	virtual void TimelinePullBack() PURE_VIRTUAL(APlayerBase::TimelinePullBack, ;);

	FOnTimelineEvent FinishedFunction{};
	FOnTimelineEvent PullBackFunction{};


	virtual void MoveForward(float value) PURE_VIRTUAL(APlayerBase::MoveForward, ;);
	virtual void Lookup(float value) PURE_VIRTUAL(APlayerBase::Lookup, ;);
	
};
