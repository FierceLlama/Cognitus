// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpeechBubbleBase.h"
#include "SpeechBubbleBuff.generated.h"

/**
 * 
 */
UCLASS()
class VOODOOMAMAJUJU_API ASpeechBubbleBuff : public ASpeechBubbleBase
{
	GENERATED_BODY()

public:

	void OnBeginTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	
};
