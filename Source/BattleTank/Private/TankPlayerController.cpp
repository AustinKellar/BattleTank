// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is posessing %s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController is not posessing a tank!"));
		return;
	}
	UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController could not find a TankAimingComponent at BeginPlay!"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(ControlledTank))
	{
		return;
	}

	FVector HitLocation;
	if (GetCrossHairRayHitLocation(HitLocation))
	{
		ControlledTank->AimAt(HitLocation);
	}
}


// Gets location of raycast through terrain. Returns true if raycast hits terrain.
bool ATankPlayerController::GetCrossHairRayHitLocation(FVector& OutHitLocation) const
{
	FVector CrossHairLookDirection;
	GetCrossHairLookDirection(CrossHairLookDirection);
	bool HitLocationIsOnTerrain = GetLookDirectionHitLocation(CrossHairLookDirection, OutHitLocation);
	return HitLocationIsOnTerrain;
}

bool ATankPlayerController::GetLookDirectionHitLocation(const FVector& LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector::ZeroVector;
	return false;
}

void ATankPlayerController::GetCrossHairLookDirection(FVector& OutLookDirection) const
{
	FVector2D CrossHairScreenLocation;
	GetCrossHairScreenLocation(CrossHairScreenLocation);

	FVector _;
	DeprojectScreenPositionToWorld(CrossHairScreenLocation.X, CrossHairScreenLocation.Y, _, OutLookDirection);
}


// Gets location of the UI crosshair on the screen.
void ATankPlayerController::GetCrossHairScreenLocation(FVector2D& OutScreenLocation) const
{
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	OutScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);
}