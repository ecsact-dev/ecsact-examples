// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ecsact/runtime/common.h"
#include "EcsactUnrealFpsProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config = Game)

class AEcsactUnrealFpsProjectile : public AActor {
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = Movement,
		meta = (AllowPrivateAccess = "true")
	)
	UProjectileMovementComponent* ProjectileMovement;

public:
	ecsact_entity_id Entity = ECSACT_INVALID_ID(entity);

	AEcsactUnrealFpsProjectile();

	auto BeginDestroy() -> void override;

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,
		AActor*              OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector              NormalImpulse,
		const FHitResult&    Hit
	);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const {
		return CollisionComp;
	}

	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const {
		return ProjectileMovement;
	}
};
