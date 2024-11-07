#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "EcsactUnrealFps__ecsact__ue.h"
#include "EcsactProjectileEntitySpawner.generated.h"

UCLASS()

class UEcsactProjectileEntitySpawner : public UExampleFpsEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT

	TMap<int32, AActor*> ProjectileActors;

	auto CreateInitialEntities() -> void;

public:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AEcsactUnrealFpsProjectile> ProjectileClass;

	auto RunnerStart_Implementation( //
		class UEcsactRunner* Runner
	) -> void override;

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
