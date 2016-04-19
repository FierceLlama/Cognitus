// Fill out your copyright notice in the Description page of Project Settings.

#include "VoodooMamaJuju.h"
#include "VoodooMamaJujuGameMode.h"
#include "Player/DefaultPlayer.h"

AVoodooMamaJujuGameMode::AVoodooMamaJujuGameMode(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	DefaultPawnClass = ADefaultPlayer::StaticClass();
}

void AVoodooMamaJujuGameMode::StartPlay()
{}

