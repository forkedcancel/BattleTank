// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {
    Super::BeginPlay();
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit ) {
    DriveTrack();
    ApplySidewaysForce();
    CurrentThrottle = 0.f;
}

void UTankTrack::ApplySidewaysForce() const {// Calculate slipping speed
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

    // Work out the required acceleration this frame to correct
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

    // Calculate and apply sideways force (F = ma)
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) {
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack() const {
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();

    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}