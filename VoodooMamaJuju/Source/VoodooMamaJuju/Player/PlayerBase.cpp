// Fill out your copyright notice in the Description page of Project Settings.

#include "VoodooMamaJuju.h"
#include "PlayerBase.h"


// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create timeline curve information
	BuffTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("BuffDebuffTimeline"));
	FinishedFunction.BindUFunction(this, FName{ TEXT("TimelineFinished") });
	BuffTimeline->SetTimelineFinishedFunc(FinishedFunction);
	BuffTimeline->SetTimelineLength(5.0f);
	BuffTimeline->SetTimelineLengthMode(TL_TimelineLength);

	PullBackTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("PullBackTimeline"));
	PullBackFunction.BindUFunction(this, FName{ TEXT("TimelinePullBack") });
	PullBackTimeline->SetTimelineLength(2.5f);
	PullBackTimeline->SetTimelinePostUpdateFunc(PullBackFunction);
	PullBackTimeline->SetTimelineLengthMode(TL_TimelineLength);

	pFade = CreateDefaultSubobject<UTimelineComponent>(TEXT("Fade"));
	FadeFinishedFunction.BindUFunction(this, FName{ TEXT("FadeFinished") });
	FadeUpdateFunction.BindUFunction(this, FName{ TEXT("FadeUpdate") });
	pFade->SetTimelineFinishedFunc(FadeFinishedFunction);
	pFade->SetTimelineLength(10.0f);
	pFade->SetTimelinePostUpdateFunc(FadeUpdateFunction);
	pFade->SetTimelineLengthMode(TL_TimelineLength);
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	//Apparently UPROPERTY variables don't get set during the ctor b/c Unreal
	//so the check happens here in BeginPlay

	normalAcceleration = 4000;
	buffAcceleration = 6000;
	debuffAcceleration = 2500;
	normalBrakingDeceleration = 1750;
	buffBrakingDeceleration = 5000;
	debuffBrakingDeceleration = 250;
	isBuffed = false;
	isDebuffed = false;
	normalBoomLength = 650;
	buffBoomLength = 1000;
	debuffBoomLength = 400;

	GetCharacterMovement()->MaxWalkSpeed = 250000;
	GetCharacterMovement()->GroundFriction = 1.0f;

	NormalMovement();
	
}

// Called every frame
void APlayerBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void APlayerBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	//Super::SetupPlayerInputComponent(InputComponent);
	check(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerBase::MoveForward);
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APlayerBase::Lookup);
}