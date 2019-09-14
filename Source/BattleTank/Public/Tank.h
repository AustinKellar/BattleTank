// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class UTankTrack;
class AProjectile;

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

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetLeftTrackReference(UTankTrack* TrackToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetRightTrackReference(UTankTrack* TrackToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	// Custom Methods	
	void AimAt(const FVector& Location);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:	

	// UPROPERTIES
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	double ReloadTime = 3.0f;

	// Fields
	double LastFireTime = 0.0f;
	UTankBarrel* Barrel = nullptr;
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	// Engine Methods
	ATank();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Custom Methods
};
