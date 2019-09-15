// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetControlledTank();
	PlayerTank = GetPlayerTank();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtPlayer();
	MoveTowardsPlayer();
	ControlledTank->Fire();
}

ATank* ATankAIController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank()
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::AimAtPlayer()
{
	if (!ensure(PlayerTank && ControlledTank))
	{
		return;
	}

	ControlledTank->AimAt(PlayerTank->GetActorLocation());
}

void ATankAIController::MoveTowardsPlayer()
{
	if (!ensure(PlayerTank && ControlledTank))
	{
		return;
	}
	MoveToActor(PlayerTank, AcceptanceRadius);
}
