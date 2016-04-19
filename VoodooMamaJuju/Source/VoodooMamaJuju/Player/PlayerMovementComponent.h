// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "PlayerMovementComponent.generated.h"

UENUM(BlueprintType)
namespace EPlayerMovement
{
	enum Type
	{
		E_Charging	UMETA(DisplayName = "Charging"),
		E_Sliding	UMETA(DisplayName = "Sliding"),
		E_NoMovement	UMETA(DisplayName = "NoMovement")
	};
}

class APlayerBase;

/**
 * 
 */
UCLASS(abstract)
class VOODOOMAMAJUJU_API UPlayerMovementComponent : public UObject
{
	GENERATED_BODY()
	
	
private:
	TEnumAsByte<EPlayerMovement::Type> m_PlayerMovementType;

protected:
	APlayerBase* m_Player;

public:
	UPlayerMovementComponent();
	UPlayerMovementComponent(TEnumAsByte<EPlayerMovement::Type> PlayerMovementType);

	FORCEINLINE const TEnumAsByte<EPlayerMovement::Type> GetPlayerMovementType() const { return m_PlayerMovementType; }

	virtual void CalculatePlayerVelocity() const PURE_VIRTUAL(UPlayerMovementComponent::CalculatePlayerVelocity, ;);
	
	static UPlayerMovementComponent* CreateAndInit(const TEnumAsByte<EPlayerMovement::Type> PlayerMovementType, APlayerBase* Player);
};

/**
*
*/
UCLASS()
class VOODOOMAMAJUJU_API UPlayerNoMovementComponent : public UPlayerMovementComponent
{
	GENERATED_BODY()

public:
	void CalculatePlayerVelocity() const override;

};

/**
*
*/
UCLASS()
class VOODOOMAMAJUJU_API UPlayerChargingMovementComponent : public UPlayerMovementComponent
{
	GENERATED_BODY()

public:
	void CalculatePlayerVelocity() const override;

};

/**
*
*/
UCLASS()
class VOODOOMAMAJUJU_API UPlayerSlidingMovementComponent : public UPlayerMovementComponent
{
	GENERATED_BODY()

public:
	void CalculatePlayerVelocity() const override;

};