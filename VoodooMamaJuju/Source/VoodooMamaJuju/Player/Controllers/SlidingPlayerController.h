// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "SlidingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VOODOOMAMAJUJU_API ASlidingPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASlidingPlayerController(const FObjectInitializer& ObjectInitializer);
	virtual void SetupInputComponent() override;

	void OnLookup(float Val);
	void OnTurn(float Val);

	void OnMoveForwardPressed();
	void OnMoveForwardReleased();
};
