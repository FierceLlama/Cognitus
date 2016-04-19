// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerVolumeBase.h"
#include "TriggerVolumeBuff.generated.h"

/**
 * 
 */
UCLASS()
class VOODOOMAMAJUJU_API ATriggerVolumeBuff : public ATriggerVolumeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "BuffZone")
	void OnBeginTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintCallable, Category = "BuffZone")
	void OnEndTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
