// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponentReference);

private:
	// UPROPERTIES
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	// Engine Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Custom Methods
	UTankAimingComponent* GetAimingComponent();
	void AimTowardsCrosshair();
	bool GetCrossHairRayHitLocation(FVector& OutHitLocation) const; // returns true if hits terrain
	bool GetLookDirectionHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const;
	bool GetCrossHairLookDirection(FVector& OutLookDirection) const;
	void GetCrossHairScreenLocation(FVector2D& OutScreenLocation) const;
};
