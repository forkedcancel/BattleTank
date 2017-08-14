// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {
    HitLocation = FVector(1.0f);

    // De-project the screen position of the crosshair to a world direction
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    UE_LOG(LogTemp, Warning, TEXT("Reticle Location: %s"), *ScreenLocation.ToString());

    return true;
}

FVector ATankPlayerController::GetLineReachStart() {
    FRotator PlayerViewPointRotation;
    FVector PlayerViewPointLocation;
    GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

    return PlayerViewPointLocation;
}

FVector ATankPlayerController::GetLineReachEnd() {
    FRotator PlayerViewPointRotation;
    FVector PlayerViewPointLocation;
    GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

    return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * 100.f;
}