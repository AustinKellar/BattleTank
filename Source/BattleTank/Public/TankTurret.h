// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void RotateHorizontal(float RelativeSpeed);

private:
	// UPROPERTIES
	UPROPERTY(EditDefaultsOnly, Category = "Elevation")
	float MaxDegreesPerSecond = 25.0f;
};
