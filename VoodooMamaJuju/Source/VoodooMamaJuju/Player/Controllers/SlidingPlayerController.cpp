// Fill out your copyright notice in the Description page of Project Settings.

#include "VoodooMamaJuju.h"
#include "SlidingPlayerController.h"
#include "../PlayerBase.h"

ASlidingPlayerController::ASlidingPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ASlidingPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	if (InputComponent)
	{
		//Bind Actions
		//InputComponent->BindAction("MoveForward", IE_Pressed, this, &ASlidingPlayerController::OnMoveForwardPressed);
		//InputComponent->BindAction("MoveForward", IE_Released, this, &ASlidingPlayerController::OnMoveForwardReleased);

		//Bind Axes
		//InputComponent->BindAxis("LookUp", this, &ASlidingPlayerController::OnLookup);
		//InputComponent->BindAxis("Turn", this, &ASlidingPlayerController::OnTurn);
	}

	else
	{
		//UE_log
	}
}


void ASlidingPlayerController::OnMoveForwardPressed()
{
	APlayerBase* Player = Cast<APlayerBase>(GetCharacter());

	if (Player)
	{
		//Player->OnMoveForwardPressed();
	}
}

void ASlidingPlayerController::OnMoveForwardReleased()
{
	APlayerBase* Player = Cast<APlayerBase>(GetCharacter());

	if (Player)
	{
		//Player->OnMoveForwardReleased();
	}
}

void ASlidingPlayerController::OnLookup(float Val)
{

}

void ASlidingPlayerController::OnTurn(float Val)\
{

}