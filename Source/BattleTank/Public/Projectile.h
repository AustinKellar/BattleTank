// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

public:	
	// Custom Methods
	void LaunchProjectile(float LaunchSpeed);


private:

	// Engine Methods
	AProjectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Custom Methods

	UProjectileMovementComponent* ProjectileMovement;

};
