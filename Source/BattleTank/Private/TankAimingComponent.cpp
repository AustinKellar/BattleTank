// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	AimDirection = FVector::ForwardVector;
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - LastFireTime) <= ReloadTime)
	{
		FiringState = EFiringState::Reloading;
		UE_LOG(LogTemp, Warning, TEXT("%s: Reloading"), *GetOwner()->GetName());
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
		UE_LOG(LogTemp, Warning, TEXT("%s: Aiming"), *GetOwner()->GetName());
	}
	else
	{
		FiringState = EFiringState::Locked;
		UE_LOG(LogTemp, Warning, TEXT("%s: Locked"), *GetOwner()->GetName());
	}
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::Reloading)
	{
		return;
	}

	if (!ensure(Barrel))
	{
		return;
	}

	if (!ensure(ProjectileBlueprint))
	{
		return;
	}

	LastFireTime = FPlatformTime::Seconds();

	AProjectile* NewProjectile =
		GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

	NewProjectile->LaunchProjectile(LaunchSpeed);
}

void UTankAimingComponent::AimAt(const FVector& Location)
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}

	FVector LaunchVelocity;
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, Barrel->GetSocketLocation(FName("Projectile")), Location, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->RotateHorizontal(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
	{
		return false;
	}

	return !Barrel->GetForwardVector().Equals(AimDirection, 0.01f);
}

