// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed) {
    float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    auto RotationChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

    SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}

