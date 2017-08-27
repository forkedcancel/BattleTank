// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
    auto ClampedThrottle = FMath::Clamp<float>(Throttle, -1.f, 1.f);
    auto ForceApplied = GetForwardVector() * ClampedThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();

    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}