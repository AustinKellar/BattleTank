// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float AcceptanceRadius = 5500;

private:
	// Engine Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Custom Methods
	APawn* GetPlayerTank();
	UTankAimingComponent* GetAimingComponent();
	void AimAtPlayer();
	void MoveTowardsPlayer();
	void FireAtPlayer();
};
