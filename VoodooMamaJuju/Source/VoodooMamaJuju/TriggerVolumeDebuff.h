// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerVolumeBase.h"
#include "TriggerVolumeDebuff.generated.h"

/**
 * 
 */
UCLASS()
class VOODOOMAMAJUJU_API ATriggerVolumeDebuff : public ATriggerVolumeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "DebuffZone")
	void OnBeginTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintCallable, Category = "DebuffZone")
	void OnEndTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
	
};
