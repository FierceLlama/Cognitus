// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SpeechBubbleBase.generated.h"

UCLASS(abstract)
class VOODOOMAMAJUJU_API ASpeechBubbleBase : public ACharacter
{
	GENERATED_BODY()

private:
	

public:	
	// Sets default values for this actor's properties
	ASpeechBubbleBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintNativeEvent, Category=Trigger)
	void OnBeginTriggerOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category=Trigger)
	void OnTestingThisShit();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Stuff)
	float RunningTime;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Stuff)
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Sound)
	UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stuff)
	TArray<AActor*> PatrolLocations;
};
