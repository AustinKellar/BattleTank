// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Blueprint Callable Functions
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

private:
	// UPROPERTIES
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	// Fields
	ATank* ControlledTank;

	// Engine Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Custom Methods
	void AimTowardsCrosshair();
	bool GetCrossHairRayHitLocation(FVector& OutHitLocation) const; // returns true if hits terrain
	bool GetLookDirectionHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const;
	void GetCrossHairLookDirection(FVector& OutLookDirection) const;
	void GetCrossHairScreenLocation(FVector2D& OutScreenLocation) const;
};
