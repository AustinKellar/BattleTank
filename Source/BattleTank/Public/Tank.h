// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Fields

	// Blueprint Callable Methods
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	// Custom Methods	
	void AimAt(const FVector& Location);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:	

	// UPROPERTIES
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000;

	// Engine Methods
	ATank();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Custom Methods
};
