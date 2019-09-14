// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTrack.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	if (!Barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("Tank could not set Barrel reference!"))
	}
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::SetLeftTrackReference(UTankTrack* TrackToSet)
{
	LeftTrack = TrackToSet;
	if (!LeftTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("Tank could not set Left Track reference!"));
	}
}

void ATank::SetRightTrackReference(UTankTrack* TrackToSet)
{
	RightTrack = TrackToSet;
	if (!RightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("Tank could not set Right Track reference!"));
	}
}

void ATank::Fire()
{
	bool bReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (!Barrel || !bReloaded)
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
	TankAimingComponent->AimAt(Location, LaunchSpeed);
}