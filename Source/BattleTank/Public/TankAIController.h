// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	// Fields
	ATank* ControlledTank = nullptr;
	ATank* PlayerTank = nullptr;
	UTankAimingComponent* AimingComponent;
	float AcceptanceRadius = 3000;

	// Engine Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Custom Methods
	ATank* GetControlledTank();
	ATank* GetPlayerTank();
	void AimAtPlayer();
	void MoveTowardsPlayer();
};
