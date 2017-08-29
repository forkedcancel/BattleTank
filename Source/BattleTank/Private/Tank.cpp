// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
    Super::BeginPlay();

    TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
    Barrel = FindComponentByClass<UTankBarrel>();
}

void ATank::Fire() {

    if (!ensure(Barrel)) { return; }

    bool isReloaded = FGenericPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds;
    if (isReloaded) {
        // Spawn a projectile at the socket location
        //TankAimingComponent->GetBarrelSocketLocation
        //TankAimingComponent->GetBarrelSocketRotation
        auto SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
        auto SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FGenericPlatformTime::Seconds();
    }
}

void ATank::AimAt(FVector HitLocation) {
    if (!ensure(TankAimingComponent)) { return; }
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}