// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

ATankAIController::ATankAIController() {
    PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto ControlledTank = Cast<ATank>(GetPawn());
    AimTowardsPlayer(ControlledTank, PlayerTank);
}

void ATankAIController::AimTowardsPlayer(ATank *ControlledTank, ATank* PlayerTank) {
    if (!ControlledTank) { return; }

    if (PlayerTank) {
        // TODO Move towards player
        MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

        // Aim towards player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        // Fire when ready
        ControlledTank->Fire();
    }

}
