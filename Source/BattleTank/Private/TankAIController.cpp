// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtPlayer();
	MoveTowardsPlayer();
	FireAtPlayer();
}

UTankAimingComponent* ATankAIController::GetAimingComponent()
{
	return GetPawn()->FindComponentByClass<UTankAimingComponent>();;
}

APawn* ATankAIController::GetPlayerTank()
{
	return GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ATankAIController::AimAtPlayer()
{
	APawn* PlayerTank = GetPlayerTank();
	UTankAimingComponent* AimingComponent = GetAimingComponent();

	if (!ensure(PlayerTank && AimingComponent))
	{
		return;
	}

	AimingComponent->AimAt(PlayerTank->GetActorLocation());
}

void ATankAIController::MoveTowardsPlayer()
{
	APawn* PlayerTank = GetPlayerTank();
	if (!ensure(PlayerTank))
	{
		return;
	}
	MoveToActor(PlayerTank, AcceptanceRadius);
}

void ATankAIController::FireAtPlayer()
{
	UTankAimingComponent* AimingComponent = GetAimingComponent();
	if (!ensure(AimingComponent))
	{
		return;
	}
	AimingComponent->Fire();
}
