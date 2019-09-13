// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Custom Methods
	void Elevate(float RelativeSpeed);

private:
	// UPROPERTIES
	UPROPERTY(EditAnywhere, Category = Elevation)
	float MaxDegreesPerSecond = 5.0f;

	UPROPERTY(EditAnywhere, Category = Elevation)
	float MaxElevationDegrees = 35.0f;

	UPROPERTY(EditAnywhere, Category = Elevation)
	float MinElevationDegrees = 0.0f;
};
