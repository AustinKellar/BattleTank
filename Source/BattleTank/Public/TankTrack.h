// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Movement)
	void SetThrottle(float Throttle);

private:
	// Max track force in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Driving)
	float MaxDrivingForce = 25000000; // Assume 40 ton tank and 1g acceleration
};
