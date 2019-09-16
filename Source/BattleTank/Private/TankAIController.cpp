// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = GetPlayerTank();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtPlayer();
	MoveTowardsPlayer();
	AimingComponent->Fire();
}

APawn* ATankAIController::GetPlayerTank()
{
	return GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ATankAIController::AimAtPlayer()
{
	if (!ensure(PlayerTank && AimingComponent))
	{
		return;
	}

	AimingComponent->AimAt(PlayerTank->GetActorLocation());
}

void ATankAIController::MoveTowardsPlayer()
{
	if (!ensure(PlayerTank))
	{
		return;
	}
	MoveToActor(PlayerTank, AcceptanceRadius);
}
