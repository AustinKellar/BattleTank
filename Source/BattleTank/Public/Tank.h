// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Fields

	// Blueprint Callable Methods
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	// Custom Methods	
	void AimAt(const FVector& Location);

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:	

	// UPROPERTIES
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	double ReloadTime = 3.0f;

	// Fields
	double LastFireTime = 0.0f;
	UTankBarrel* Barrel = nullptr;

	// Engine Methods
	ATank();

	// Custom Methods
};
