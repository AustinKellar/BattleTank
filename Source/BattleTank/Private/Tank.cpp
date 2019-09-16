// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	Barrel = FindComponentByClass<UTankBarrel>();
}

void ATank::Fire()
{
	bool bReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (!ensure(Barrel) || !bReloaded)
	{
		return;
	}

	LastFireTime = FPlatformTime::Seconds();

	AProjectile* NewProjectile = 
		GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

	NewProjectile->LaunchProjectile(LaunchSpeed);
}

void ATank::AimAt(const FVector& Location)
{
	if (!ensure(TankAimingComponent))
	{
		return;
	}

	TankAimingComponent->AimAt(Location, LaunchSpeed);
}