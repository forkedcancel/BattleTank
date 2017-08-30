// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController {
    GENERATED_BODY()


protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
    ATankPlayerController();

    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000.f;

    // Start the tank moving the barrel so that a shot would hit where
    // the crosshair intersects the world
    void AimTowardsCrosshair();

    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5;

    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333;


    bool GetSightRayHitLocation(FVector &HitLocation) const;

    bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;

    FVector2D GetScreenLocation() const;

    bool GetLookVectorHitLocation(FVector &HitLocation, FVector &LookDirection) const;
};
