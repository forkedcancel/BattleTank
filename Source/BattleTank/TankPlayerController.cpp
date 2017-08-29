// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

// Sets default values
ATankPlayerController::ATankPlayerController() {
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

ATank *ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
    if (ensure(AimingComponent)) {
        FoundAimingComponent(AimingComponent);
    }
}

void ATankPlayerController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
    if (!ensure(GetControlledTank())) { return; }

    FVector HitLocation; // Out parameter
    // If it hits landscape
    if (GetSightRayHitLocation(HitLocation)) {
        // Tell controlled tank to aim at this point
        GetControlledTank()->AimAt(HitLocation);
    }
}

// De-project the screen position of the crosshair to a world direction
FVector2D ATankPlayerController::GetScreenLocation() const {
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    return FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
}

// Get world location through crosshair
bool ATankPlayerController::GetLookVectorHitLocation(FVector &HitLocation, FVector &LookDirection) const {
    FHitResult HitResult;

    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + LookDirection * LineTraceRange;
    bool IsHitFound = GetWorld()->LineTraceSingleByChannel(
            HitResult,
            StartLocation,
            EndLocation,
            ECC_Visibility
    );

    // Set OUT var
    HitLocation = HitResult.Location;

    return IsHitFound;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {

    FVector LookDirection;
    if (GetLookDirection(GetScreenLocation(), LookDirection)) {
        return GetLookVectorHitLocation(HitLocation, LookDirection);
    }

    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const {
    FVector WorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}
