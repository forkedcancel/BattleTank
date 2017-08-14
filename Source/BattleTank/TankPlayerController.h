// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

    ATankPlayerController();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    ATank* GetControlledTank() const;

protected:
	virtual void BeginPlay() override;
};
