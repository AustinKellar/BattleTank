// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController has posessed %s"), *ControlledTank->GetName());
	}

	PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController has found Player Tank: %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtPlayer();
	ControlledTank->Fire();
	ATank* Player = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	MoveToActor(Player, AcceptanceRadius);
}

ATank* ATankAIController::GetControlledTank()
{
	ATank* Tank = Cast<ATank>(GetPawn());
	
	if (!Tank)
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController did not posess a tank!"));
	}

	return Tank;
}

ATank* ATankAIController::GetPlayerTank()
{

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController could not find Player tank!"));
	}

	return PlayerTank;
}

void ATankAIController::AimAtPlayer()
{
	if (!PlayerTank || !ControlledTank)
	{
		return;
	}

	ControlledTank->AimAt(PlayerTank->GetActorLocation());
}
