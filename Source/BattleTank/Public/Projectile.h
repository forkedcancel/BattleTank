// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

    void LaunchProjectile(float Speed);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* LaunchBlast = nullptr;

    UPROPERTY(VisibleAnywhere)
    UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere)
    URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DamageAmount = 20.f;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	void OnTimerExpire();
};
