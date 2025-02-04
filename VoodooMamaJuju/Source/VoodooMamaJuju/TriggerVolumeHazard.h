// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerVolumeBase.h"
#include "TriggerVolumeHazard.generated.h"

/**
 * 
 */
UCLASS()
class VOODOOMAMAJUJU_API ATriggerVolumeHazard : public ATriggerVolumeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "DeathZone")
	void OnBeginTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	
};
