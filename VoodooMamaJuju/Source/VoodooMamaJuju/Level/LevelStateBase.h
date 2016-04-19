// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "LevelStateProps.h"
#include "LevelStateBase.generated.h"
/**
 * 
 */
UCLASS(abstract)
class VOODOOMAMAJUJU_API ALevelStateBase : public AGameState
{
	GENERATED_BODY()

public:
	virtual const FLevelStateProps ToLevelStateProps() const PURE_VIRTUAL(ALevelStateBase::ToLevelStateProps, return *((FLevelStateProps*)0););
};
