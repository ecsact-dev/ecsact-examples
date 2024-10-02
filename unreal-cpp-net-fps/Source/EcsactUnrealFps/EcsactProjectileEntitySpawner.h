#pragma once

#include "CoreMinimal.h"
#include "EcsactUnrealFps__ecsact__ue.h"
#include "EcsactProjectileEntitySpawner.generated.h"

UCLASS()

class UEcsactProjectileEntitySpawner : public UExampleFpsEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT

	TMap<int32, AActor*> ProjectileActors;

public:
	auto InitProjectile_Implementation( //
		int32                 Entity,
		FExampleFpsProjectile Projectile
	) -> void override;
	auto RemoveProjectile_Implementation( //
		int32                 Entity,
		FExampleFpsProjectile Projectile
	) -> void override;

	auto UpdatePosition_Implementation( //
		int32               Entity,
		FExampleFpsPosition Position
	) -> void override;
};
