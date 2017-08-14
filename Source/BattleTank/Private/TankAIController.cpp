// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

ATank *ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay() {
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) {
        UE_LOG(LogTemp, Error, TEXT("TankAIController not possessing a tank!"))
    } else {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController possessing %s"), *(ControlledTank->GetName()));
    }

    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank) {
        UE_LOG(LogTemp, Error, TEXT("PlayerTank not found!"))
    } else {
        UE_LOG(LogTemp, Warning, TEXT("PlayerTank possessing %s"), *(PlayerTank->GetName()));
    }
}

ATank *ATankAIController::GetPlayerTank() const {
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
