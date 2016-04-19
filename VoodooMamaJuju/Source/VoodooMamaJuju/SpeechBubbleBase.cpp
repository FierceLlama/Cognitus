// Fill out your copyright notice in the Description page of Project Settings.

#include "VoodooMamaJuju.h"
#include "SpeechBubbleBase.h"


// Sets default values
ASpeechBubbleBase::ASpeechBubbleBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create initial volume
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->AttachTo(GetCapsuleComponent());
	SphereComponent->InitSphereRadius(100.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpeechBubbleBase::OnBeginTriggerOverlap);

	//add audio component
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComp->AttachTo(GetCapsuleComponent());

	//set the sound component
	/*static ConstructorHelpers::FObjectFinder<USoundWave> SoundCue(TEXT("/Game/Assets/Sounds/Sneeze"));
	if (SoundCue.Succeeded())
	{
		AudioComp->SetSound(SoundCue.Object);
	}
	//set the attenuation
	static ConstructorHelpers::FObjectFinder<USoundAttenuation> SoundAtten(TEXT("/Game/Assets/Sounds/SphereAttenuation"));
	if (SoundAtten.Succeeded())
	{
		AudioComp->AttenuationSettings = SoundAtten.Object;
	}*/

	// Create and position a mesh component so we can see where our sphere is
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Engine/BasicShapes/Sphere"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SphereVisualAsset(TEXT("/Game/Entities/ThoughtBubble/Animations/Thought_Bubble_Rig"));
	if (SphereVisualAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SphereVisualAsset.Object);
		GetMesh()->SetCollisionProfileName(TEXT("Trigger"));
	}
}

// Called when the game starts or when spawned
void ASpeechBubbleBase::BeginPlay()
{
	Super::BeginPlay();

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString("Started"));

}

// Called every frame
void ASpeechBubbleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpeechBubbleBase::OnBeginTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Hit Detected!"));
	}
}

//called from the in blueprint collision (this is only a test for blueprint callable events)
void ASpeechBubbleBase::OnTestingThisShit()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Shit Tested!"));

}