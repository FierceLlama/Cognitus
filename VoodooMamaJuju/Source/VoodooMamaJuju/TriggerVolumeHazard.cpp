// Fill out your copyright notice in the Description page of Project Settings.

#include "VoodooMamaJuju.h"
#include "TriggerVolumeHazard.h"
#include "Player/PlayerBase.h"


void ATriggerVolumeHazard::OnBeginTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && ((OtherActor->GetClass()->IsChildOf(APlayerBase::StaticClass()))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString("Dead!"));

		UGameplayStatics::OpenLevel(GetWorld(), "ContinueScreen");

	}
}







