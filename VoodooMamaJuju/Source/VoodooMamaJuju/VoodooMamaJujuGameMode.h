// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "VoodooMamaJujuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VOODOOMAMAJUJU_API AVoodooMamaJujuGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AVoodooMamaJujuGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;
	
	
};
