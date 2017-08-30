// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/StaticMesh.h"
#include <EngineClasses.h>
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialize(UTankBarrel* Barrel, UTankTurret* Turret) {
    if (!ensure(Barrel && Turret)) { return; }
    this->Barrel = Barrel;
    this->Turret = Turret;
}

void UTankAimingComponent::Fire() {
    if (!ensure(Barrel)) { return; }

    bool isReloaded = FGenericPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds;
    if (isReloaded) {
        // Spawn a projectile at the socket location
        auto SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
        auto SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FGenericPlatformTime::Seconds();
    }
}

void UTankAimingComponent::AimAt(FVector HitLocation) {

    if (!ensure(Barrel && Turret)) { return; }

    auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    FVector OutLaunchVelocity;

    // Calculate the OutLaunchVelocity
    auto bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
                this,
                OutLaunchVelocity,
                StartLocation,
                HitLocation,
                LaunchSpeed,
                false,
                0,
                0,
                ESuggestProjVelocityTraceOption::DoNotTrace
        );

    if (bHaveAimSolution) {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
    if (!ensure(Barrel && Turret)) { return; }

    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    Barrel->Elevate(DeltaRotator.Pitch);
    Turret->Rotate(DeltaRotator.Yaw);
}