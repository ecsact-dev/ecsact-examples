
#pragma once

#include <tuple>
#include <optional>

#include "CoreMinimal.h"
#include "MassEntityConfigAsset.h"
#include "EcsactUnrealFps__ecsact__ue.h"
#include "MassEntitySpawnDataGeneratorBase.h"
#include "MassEntityTypes.h"
#include "Ecsact/runtime/common.h"
#include "EcsactEntityMassSpawner.generated.h"

UCLASS(Abstract)

// TODO(Kelwan): MassSpawner does more than its name implies and should be
// separated before merging to main
class UEcsactEntityMassSpawner : public UExampleFpsEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT

	UPROPERTY(EditAnywhere)
	UMassEntityConfigAsset* MassEntityConfigAsset;

	UPROPERTY(EditAnywhere)
	TArray<UMassEntitySpawnDataGeneratorBase*> SpawnDataGenerators;

	TMap<ecsact_entity_id, TArray<FMassEntityHandle>> MassEntities;

	using EntityPoolT = std::tuple<
		std::optional<FExampleFpsMassentity>,
		std::optional<FExampleFpsPosition>>;

	// NOTE: Temporary until more general solution is implemented
	TMap<ecsact_entity_id, EntityPoolT> EntityPools;

	void Spawn(ecsact_entity_id Entity, const FExampleFpsPosition& Position);

public:
	UFUNCTION(BlueprintCallable) void CreateMassEntities(int count);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StreamEntities;

	auto InitMassentity_Implementation( //
		int32                 Entity,
		FExampleFpsMassentity MassEntity
	) -> void override;

	auto InitPosition_Implementation( //
		int32               Entity,
		FExampleFpsPosition Position
	) -> void override;

	auto UpdatePosition_Implementation( //
		int32               Entity,
		FExampleFpsPosition Position
	) -> void override;

	auto UpdateToggle_Implementation( //
		int32             Entity,
		FExampleFpsToggle Toggle
	) -> void override;

	auto Push(int32 PlayerId) -> void;
};
