// Fill out your copyright notice in the Description page of Project Settings.

#include "VoodooMamaJuju.h"
#include "TriggerVolumeBase.h"


// Sets default values
ATriggerVolumeBase::ATriggerVolumeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(50, 50, 50));
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATriggerVolumeBase::OnBeginTriggerOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ATriggerVolumeBase::OnEndTriggerOverlap);

	// Create and position a mesh component so we can see where our box is
	//remove this for when we need it to just be a trigger
	BoxVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	BoxVisual->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("/Engine/BasicShapes/Cube"));
	if (BoxVisualAsset.Succeeded())
	{
		BoxVisual->SetStaticMesh(BoxVisualAsset.Object);
		BoxVisual->SetCollisionProfileName(TEXT("Trigger"));
	}
}

// Called when the game starts or when spawned
void ATriggerVolumeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerVolumeBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATriggerVolumeBase::OnBeginTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Hit Detected!"));
	}
}

void ATriggerVolumeBase::OnEndTriggerOverlap_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Left Zone!"));
	}
}
