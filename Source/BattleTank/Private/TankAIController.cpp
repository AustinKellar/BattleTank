// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
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
