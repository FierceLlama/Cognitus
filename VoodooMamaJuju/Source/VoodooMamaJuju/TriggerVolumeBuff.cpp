// Fill out your copyright notice in the Description page of Project Settings.

#include "VoodooMamaJuju.h"
#include "TriggerVolumeBuff.h"
#include "SpeechBubbleBase.h"
#include "Player/PlayerBase.h"


void ATriggerVolumeBuff::OnBeginTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (!(OtherActor->GetClass()->IsChildOf(ASpeechBubbleBase::StaticClass()))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString("In Buff Zone!"));
		
		for (TActorIterator<APlayerBase> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			APlayerBase *player = *ActorItr;
			ActorItr->Buff();
			ActorItr->BuffColor();
		}
	}
}

void ATriggerVolumeBuff::OnEndTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (!(OtherActor->GetClass()->IsChildOf(ASpeechBubbleBase::StaticClass()))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString("Left Buff Zone!"));

		for (TActorIterator<APlayerBase> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			APlayerBase *player = *ActorItr;
			ActorItr->SetLastingBuff();
		}
	}
}