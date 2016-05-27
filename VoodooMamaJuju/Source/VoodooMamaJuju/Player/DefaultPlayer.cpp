// Fill out your copyright notice in the Description page of Project Settings.

#include "VoodooMamaJuju.h"
#include "DefaultPlayer.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

ADefaultPlayer::ADefaultPlayer()
{
	//get mesh, inverted mesh and setup animations
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ObjectMeshAsset(TEXT("/Game/Entities/Player/Model/Ooze"));
	if (ObjectMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(ObjectMeshAsset.Object);
	}

	GetMesh()->AddRelativeRotation(FRotator(0, -90, 0));
	//GetMesh()->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	GetMesh()->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));

	static ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass> AnimBPFinder(TEXT("/Game/Entities/Player/Animations/Ooze_AnimationBP.Ooze_AnimationBP_C"));
	GetMesh()->AnimBlueprintGeneratedClass = AnimBPFinder.Object;

	//invertedMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("InvertedMesh"));
	//invertedMesh->AttachTo(GetMesh());
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> InvertedMeshAsset(TEXT("/Game/Entities/Player/Model/Ooze_Invert"));
	//if (InvertedMeshAsset.Succeeded())
	//{
	//	invertedMesh->SetSkeletalMesh(InvertedMeshAsset.Object);
	//}
	//invertedMesh->SetRelativeScale3D(FVector(.99, .99, .99));
	////invertedMesh->AnimBlueprintGeneratedClass = AnimBPFinder.Object;
	//	invertedMesh->SetMasterPoseComponent(GetMesh());
	//GetMesh()->SetMasterPoseComponent(invertedMesh);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(GetMesh());
	CameraBoom->TargetArmLength = 650; // The camera follows at this distance behind the character	
	CameraBoom->SetRelativeLocation(FVector(-150, -400, 500));
	CameraBoom->AddRelativeRotation(FRotator(0, 90, 0));
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	//FollowCamera->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(FollowCamera->RelativeLocation, UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter()->GetActorLocation()));
	//FollowCamera->AddRelativeRotation(FRotator(-40, 0, 0));
	//FollowCamera->bConstrainAspectRatio = true;
	//FollowCamera->AspectRatio = 1.6f;

	// Internal particle effects for spark, buff, and debuff
	PlayerSpark = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PlayerSpark"));
	PlayerSpark->AttachTo(GetCapsuleComponent());
	static ConstructorHelpers::FObjectFinder<UParticleSystem> sparkAsset(TEXT("/Game/Assets/Effects/PlayerSpark.PlayerSpark"));
	if (sparkAsset.Succeeded())
	{
		PlayerSpark->SetTemplate(sparkAsset.Object);
	}
	PlayerSpark->SetRelativeLocation(FVector(0, 0, 15));
	PlayerSpark->SetTranslucentSortPriority(50);

	PlayerBuff = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PlayerBuff"));
	PlayerBuff->AttachTo(GetCapsuleComponent());
	static ConstructorHelpers::FObjectFinder<UParticleSystem> buffAsset(TEXT("/Game/Assets/Effects/PlayerBuff.PlayerBuff"));
	if (buffAsset.Succeeded())
	{
		PlayerBuff->SetTemplate(buffAsset.Object);
	}
	PlayerBuff->SetTranslucentSortPriority(100);
	PlayerBuff->bAutoActivate = false;

	PlayerDebuff = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PlayerDebuff"));
	PlayerDebuff->AttachTo(GetCapsuleComponent());
	static ConstructorHelpers::FObjectFinder<UParticleSystem> debuffAsset(TEXT("/Game/Assets/Effects/PlayerDebuff.PlayerDebuff"));
	if (debuffAsset.Succeeded())
	{
		PlayerDebuff->SetTemplate(debuffAsset.Object);
	}
	PlayerDebuff->SetTranslucentSortPriority(100);
	PlayerDebuff->bAutoActivate = false;

	//get and set all materials for player and inverted player
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialInst(TEXT("/Game/Assets/Materials/Character_Translucent_Mat"));
	//static ConstructorHelpers::FObjectFinder<UMaterialInterface> InvertedMaterialInst(TEXT("/Game/Assets/Materials/InvertedCharacterMaterial"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> greenSolid(TEXT("/Game/Entities/Player/Model/Character_Green_Diffuse"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> greenOutline(TEXT("/Game/Entities/Player/Model/Character_Green_Outline_Diffuse"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> redSolid(TEXT("/Game/Entities/Player/Model/Character_Red_Diffuse"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> redOutline(TEXT("/Game/Entities/Player/Model/Character_Red_Outline_Diffuse"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> purpleSolid(TEXT("/Game/Entities/Player/Model/Character_Purple_Diffuse"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> purpleOutline(TEXT("/Game/Entities/Player/Model/Character_Purple_Outline_Diffuse"));
	DynamicMatInst = GetMesh()->CreateDynamicMaterialInstance(0, MaterialInst.Object);
	//InvertedDynamicMatInst = invertedMesh->CreateDynamicMaterialInstance(0, InvertedMaterialInst.Object);
	solidGreen = greenSolid.Object;
	outlineGreen = greenOutline.Object;
	solidRed = redSolid.Object;
	outlineRed = redOutline.Object;
	solidPurple = purpleSolid.Object;
	outlinePurple = purpleOutline.Object;
}

void ADefaultPlayer::MoveForward(float value)
{
	/*if (GetMovementComponent()->IsMovingOnGround())
	{*/
		AddMovementInput(GetActorForwardVector(), value);
		if (value > 0)
		{
			this->PlayMoving();
		}
		else if(GetMovementComponent()->IsFalling())
		{
			this->StopMoving();
		}
		else
		{
			this->StopMoving();
		}
	/*}
	else
	{
		this->StopMoving();
	}*/
}

void ADefaultPlayer::Lookup(float value)
{
	float tempPitch = this->CameraBoom->GetComponentRotation().Pitch + value;
	if (tempPitch < this->pitchUpAngle && tempPitch > this->pitchDownAngle)
	{
		this->CameraBoom->AddLocalRotation(FRotator(value, 0.0f, 0.0f));
	}
	else
	{
		if (tempPitch < this->pitchDownAngle)
		{
			this->CameraBoom->SetWorldRotation(FRotator(this->pitchDownAngle, this->CameraBoom->GetComponentRotation().Yaw, this->CameraBoom->GetComponentRotation().Roll));
		}
		else
		{
			this->CameraBoom->SetWorldRotation(FRotator(this->pitchUpAngle, this->CameraBoom->GetComponentRotation().Yaw, this->CameraBoom->GetComponentRotation().Roll));
		}
	}

	this->FollowCamera->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(FollowCamera->GetComponentLocation(), 
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter()->GetActorLocation() + (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter()->GetActorRightVector() * 150)));
}

//resets players variables to normal movement
void ADefaultPlayer::NormalMovement()
{
	GetCharacterMovement()->MaxAcceleration = normalAcceleration;
	GetCharacterMovement()->BrakingDecelerationWalking = normalBrakingDeceleration;

	//change camera distance and call the timeline to adjust
	cameraDist = normalBoomLength;
	PullBackTimeline->Stop();
	PullBackTimeline->PlayFromStart();
	PlayerBuff->SetActive(false);
	PlayerDebuff->SetActive(false);
}

//player gains buff
void ADefaultPlayer::BuffPlayer()
{
	isBuffed = true;
	GetCharacterMovement()->AddImpulse((GetActorForwardVector() * 10000));
	GetCharacterMovement()->MaxAcceleration = buffAcceleration;
    GetCharacterMovement()->BrakingDecelerationWalking = buffBrakingDeceleration;
	PlayerBuff->SetActive(true);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString("Player Buffed!!"));
}

//player gains debuff
void ADefaultPlayer::DebuffPlayer()
{
	isDebuffed = true;
	GetCharacterMovement()->Velocity = FVector(0, 0, 0);
	GetCharacterMovement()->MaxAcceleration = debuffAcceleration;
	GetCharacterMovement()->BrakingDecelerationWalking = debuffBrakingDeceleration;
	PlayerDebuff->SetActive(true);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString("Player Debuffed!!"));
}

void ADefaultPlayer::RemoveBuff()
{
	BuffTimeline->Stop();
	isBuffed = false;
	PlayerBuff->SetActive(false);
}

void ADefaultPlayer::RemoveDebuff()
{
	BuffTimeline->Stop();
	isDebuffed = false;
	PlayerDebuff->SetActive(false);
}

//player in a buff zone
void ADefaultPlayer::Buff()
{
	if (isBuffed)
	{
		BuffTimeline->Stop();
	}
	else
	{
		if (isDebuffed)
		{
			RemoveDebuff();
		}
		inBuffZone = true;
		BuffPlayer();
		
		//change camera distance and call the timeline to adjust
		cameraDist = buffBoomLength;
		PullBackTimeline->Stop();
		PullBackTimeline->PlayFromStart();
	}
}


//player in a debuff zone
void ADefaultPlayer::Debuff()
{
	if (isDebuffed)
	{
		BuffTimeline->Stop();
	}
	else
	{
		if (isBuffed)
		{
			RemoveBuff();
		}
		inDebuffZone = true;
		DebuffPlayer();

		//change camera distance and call the timeline to adjust
		cameraDist = debuffBoomLength;
		PullBackTimeline->Stop();
		PullBackTimeline->PlayFromStart();
	}
}

//left lasting buff zone
void ADefaultPlayer::SetLastingBuff()
{
	inBuffZone = false;
	BuffTimeline->ReverseFromEnd();
}

//left lasting debuff zone
void ADefaultPlayer :: SetLastingDebuff()
{
	inDebuffZone = false;
	BuffTimeline->ReverseFromEnd();
}

void ADefaultPlayer::NormalColor()
{
	DynamicMatInst->SetTextureParameterValue(FName{ TEXT("SolidTexture") }, solidGreen);
	GetMesh()->SetMaterial(0, DynamicMatInst);
	DynamicMatInst->SetTextureParameterValue(FName{ TEXT("OutlineTexture") }, outlineGreen);
	GetMesh()->SetMaterial(0, DynamicMatInst);
	/*InvertedDynamicMatInst->SetTextureParameterValue(FName{ TEXT("OutlineTexture") }, outlineGreen);
	invertedMesh->SetMaterial(0, InvertedDynamicMatInst);*/
}

void ADefaultPlayer::BuffColor()
{
 	DynamicMatInst->SetTextureParameterValue(FName{ TEXT("SolidTexture") }, solidRed);
	GetMesh()->SetMaterial(0, DynamicMatInst);
	DynamicMatInst->SetTextureParameterValue(FName{ TEXT("OutlineTexture") }, outlineRed);
	GetMesh()->SetMaterial(0, DynamicMatInst);
	/*InvertedDynamicMatInst->SetTextureParameterValue(FName{ TEXT("OutlineTexture") }, outlineRed);
	invertedMesh->SetMaterial(0, InvertedDynamicMatInst);*/
}

void ADefaultPlayer::DebuffColor()
{
	DynamicMatInst->SetTextureParameterValue(FName{ TEXT("SolidTexture") }, solidPurple);
	GetMesh()->SetMaterial(0, DynamicMatInst);
	DynamicMatInst->SetTextureParameterValue(FName{ TEXT("OutlineTexture") }, outlinePurple);
	GetMesh()->SetMaterial(0, DynamicMatInst);
	/*InvertedDynamicMatInst->SetTextureParameterValue(FName{ TEXT("OutlineTexture") }, outlinePurple);
	invertedMesh->SetMaterial(0, InvertedDynamicMatInst);*/
}

//set the character back to normal after the buff/debuff time ends
void ADefaultPlayer::TimelineFinished()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString("Finished"));
	NormalMovement();
	isBuffed = false;
	isDebuffed = false;
	NormalColor();
}

//adjust the camera based on if the player is buffed or debuffed
void ADefaultPlayer::TimelinePullBack()
{
   	CameraBoom->TargetArmLength = FMath::Lerp(CameraBoom->TargetArmLength, cameraDist, (PullBackTimeline->GetPlaybackPosition() / PullBackTimeline->GetTimelineLength()));
}

void ADefaultPlayer::FadePlayer()
{
	this->pFade->PlayFromStart();
}

void ADefaultPlayer::StopFade()
{
	this->pFade->Stop();
	/*DynamicMatInst->SetScalarParameterValue(FName{ TEXT("Blend") }, 0.0f);
	GetMesh()->SetMaterial(0, DynamicMatInst);*/
	/*InvertedDynamicMatInst->SetScalarParameterValue(FName{ TEXT("Blend") }, 0.0f);
	invertedMesh->SetMaterial(0, InvertedDynamicMatInst);*/
	this->PlayerSpark->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void ADefaultPlayer::FadeUpdate()
{
	/*DynamicMatInst->SetScalarParameterValue(FName{ TEXT("Blend") }, pFade->GetPlaybackPosition() / pFade->GetTimelineLength());
	GetMesh()->SetMaterial(0, DynamicMatInst);*/
	/*InvertedDynamicMatInst->SetScalarParameterValue(FName{ TEXT("Blend") }, pFade->GetPlaybackPosition() / pFade->GetTimelineLength());
	invertedMesh->SetMaterial(0, InvertedDynamicMatInst);*/
	this->PlayerSpark->SetRelativeScale3D(FVector(FVector(1.0f, 1.0f, 1.0f) * (1 - pFade->GetPlaybackPosition() / pFade->GetTimelineLength())));
}

void ADefaultPlayer::FadeFinished()
{
	//UGameplayStatics::OpenLevel(GetWorld(), "ContinueScreen");
	CameraLerpMatinee();
}

void ADefaultPlayer::PlayShake()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientPlayCameraShake(this->landingShake, 1.0f);
}

void ADefaultPlayer::Squish()
{
	this->PlaySquish();
}