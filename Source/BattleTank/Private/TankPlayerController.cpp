// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	if (!ensure(GetPawn()))
	{
		return;
	}

	UTankAimingComponent* AimingComponent = GetAimingComponent();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

UTankAimingComponent* ATankPlayerController::GetAimingComponent()
{
	if (!GetPawn())
	{
		return nullptr;
	}

	return GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	UTankAimingComponent* AimingComponent = GetAimingComponent();
	if (!ensure(AimingComponent))
	{
		return;
	}

	FVector HitLocation;
	if (GetCrossHairRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
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