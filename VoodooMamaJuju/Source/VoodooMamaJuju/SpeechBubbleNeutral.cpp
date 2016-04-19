// Fill out your copyright notice in the Description page of Project Settings.

#include "VoodooMamaJuju.h"
#include "SpeechBubbleNeutral.h"


void ASpeechBubbleNeutral::OnBeginTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (!(OtherActor->GetClass()->IsChildOf(ASpeechBubbleBase::StaticClass()))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString("Hit Detected On Neutral!"));
	}

}

