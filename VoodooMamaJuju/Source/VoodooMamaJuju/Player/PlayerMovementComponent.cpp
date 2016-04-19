// Fill out your copyright notice in the Description page of Project Settings.

#include "VoodooMamaJuju.h"
#include "PlayerMovementComponent.h"
#include "PlayerBase.h"

UPlayerMovementComponent::UPlayerMovementComponent()
{

}

void UPlayerNoMovementComponent::CalculatePlayerVelocity() const
{
	auto CharMovement = m_Player->GetCharacterMovement();

	if (m_Player->Controller && CharMovement)
	{
		CharMovement->Velocity = FVector::ZeroVector;
	}
}

void UPlayerChargingMovementComponent::CalculatePlayerVelocity() const
{
	auto CharMovement = m_Player->GetCharacterMovement();

	/*if (m_Player->Controller && CharMovement)
	{
		
	}*/
}

void UPlayerSlidingMovementComponent::CalculatePlayerVelocity() const
{
	//auto CharMovement = m_Player->GetCharacterMovement();

	//if (m_Player->Controller && CharMovement)
	//{
	//	m_Player->AddThrust(m_Player->ThrustAdditive);
	//	CharMovement->Velocity = (m_Player->GetActorForwardVector() * m_Player->GetThrust());
	//}
}

UPlayerMovementComponent* UPlayerMovementComponent::CreateAndInit(const TEnumAsByte<EPlayerMovement::Type> PlayerMovementType, APlayerBase* Player)
{
	const EPlayerMovement::Type MovementTypeEnum = PlayerMovementType.GetValue();

	UPlayerMovementComponent* Ret = 0;

	switch (MovementTypeEnum)
	{
		case EPlayerMovement::Type::E_NoMovement:
			Ret = NewObject<UPlayerNoMovementComponent>();
			break;
		case EPlayerMovement::Type::E_Charging:
			Ret = NewObject<UPlayerChargingMovementComponent>();
			break;
		case EPlayerMovement::Type::E_Sliding:
			Ret = NewObject<UPlayerSlidingMovementComponent>();
			break;
	}

	if (Ret)
	{
		Ret->m_PlayerMovementType = PlayerMovementType;
		Ret->m_Player = Player;
	}

	return Ret;
}