// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDeathDelegate);
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

    virtual float TakeDamage(float Damage, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;
    FTankDeathDelegate OnDeath;

protected:
	virtual void BeginPlay() override;
private:
	ATank();

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	int32 CurrentHealth = StartingHealth;
};
