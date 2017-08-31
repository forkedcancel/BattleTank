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
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay() {
//    Super::BeginPlay();
    LastFireTime = FGenericPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    if ((FGenericPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
        FiringState = EFiringState::Reloading;
    } else if (IsBarrelMoving()) {
        FiringState = EFiringState::Aiming;
    } else {
        FiringState = EFiringState::Locked;
    }
}

bool UTankAimingComponent::IsBarrelMoving() {
    if (!ensure(Barrel)) { return false; }
    auto BarrelForward = Barrel->GetForwardVector();
    return !AimDirection.Equals(BarrelForward, 0.01);
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
    if (!ensure(BarrelToSet && TurretToSet)) { return; }
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::Fire() {
    if (FiringState != EFiringState::Reloading) {
        if (!ensure(Barrel)) { return; }
        if (!ensure(ProjectileBlueprint)) { return; }
        // Spawn a projectile at the socket location
        auto SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
        auto SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FGenericPlatformTime::Seconds();
    }
}

void UTankAimingComponent::AimAt(FVector HitLocation) {

    if (!ensure(Barrel)) { return; }

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
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards();
    }
}

void UTankAimingComponent::MoveBarrelTowards() {
    if (!ensure(Barrel && Turret)) { return; }

    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    Barrel->Elevate(DeltaRotator.Pitch);
    Turret->Rotate(DeltaRotator.Yaw);
}