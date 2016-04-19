// Fill out your copyright notice in the Description page of Project Settings.

#include "VoodooMamaJuju.h"
#include "TriggerVolumeDebuff.h"
#include "SpeechBubbleBase.h"
#include "Player/PlayerBase.h"


void ATriggerVolumeDebuff::OnBeginTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (!(OtherActor->GetClass()->IsChildOf(ASpeechBubbleBase::StaticClass()))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString("In Debuff Zone!"));

		for (TActorIterator<APlayerBase> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			APlayerBase *player = *ActorItr;
			ActorItr->Debuff();
			ActorItr->DebuffColor();
		}
	}
}

void ATriggerVolumeDebuff::OnEndTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (!(OtherActor->GetClass()->IsChildOf(ASpeechBubbleBase::StaticClass()))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString("Left Debuff Zone!"));

		for (TActorIterator<APlayerBase> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			APlayerBase *player = *ActorItr;
			ActorItr->SetLastingDebuff();
		}
	}
}

