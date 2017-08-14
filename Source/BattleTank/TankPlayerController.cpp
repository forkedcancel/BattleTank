// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

// Sets default values
ATankPlayerController::ATankPlayerController()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

ATank *ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) {
        UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a tank!"))
    } else {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(ControlledTank->GetName()));
    }
}

void ATankPlayerController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
    if (!GetControlledTank()) { return; }

    // Get world location through crosshair

    // If it hits landscape
        // Tell controlled tank to aim at this point
}

