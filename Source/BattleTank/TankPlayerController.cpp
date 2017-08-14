// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

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

    FVector HitLocation; // Out parameter
    // If it hits landscape
    if (GetSightRayHitLocation(HitLocation)) {

        // Get world location through crosshair
        UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
        // Tell controlled tank to aim at this point
    }

}

// De-project the screen position of the crosshair to a world direction
FVector2D ATankPlayerController::GetScreenLocation() const {
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    return FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector &HitLocation, FVector &LookDirection) const {
    FHitResult HitResult;

    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + LookDirection * LineTraceRange;
    bool Result = GetWorld()->LineTraceSingleByChannel(
            HitResult,
            PlayerCameraManager->GetCameraLocation(),
            EndLocation,
            ECC_Visibility
    );

    HitLocation = HitResult.Location;
    UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

    return Result;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {

    FVector LookDirection;
    if (GetLookDirection(GetScreenLocation(), LookDirection)) {
//        UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());

        GetLookVectorHitLocation(HitLocation, LookDirection);
    }

    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const {
    FVector WorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}
