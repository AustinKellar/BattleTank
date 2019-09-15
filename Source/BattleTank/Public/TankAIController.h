// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	// Fields
	ATank* ControlledTank;
	ATank* PlayerTank;

	// Engine Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Custom Methods
	ATank* GetControlledTank();
	ATank* GetPlayerTank();
	void AimAtPlayer();
	float AcceptanceRadius = 3000;
};
