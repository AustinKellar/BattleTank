// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:	
	//UPROPERTIES
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 MaxHitPoints = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 HitPoints;

	// Engine Methods
	ATank();
	virtual void BeginPlay() override;
};
