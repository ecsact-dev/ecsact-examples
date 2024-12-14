
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

	TMap<ecsact_entity_id, TArray<FMassEntityHandle>> MassEntities;

	auto CheckMassEntities(int32 Entity, const TCHAR* EventName) -> bool;

public:
	UFUNCTION(BlueprintCallable) void CreateMassEntities(int count);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StreamEntities;

	auto EntityCreated_Implementation(int32 Entity) -> void override;

	auto EntityDestroyed_Implementation(int32 Entity) -> void override;

	auto InitEnemy_Implementation( //
		int32            Entity,
		FExampleFpsEnemy Enemy
	) -> void override;

	auto RemoveEnemy_Implementation( //
		int32            Entity,
		FExampleFpsEnemy Enemy
	) -> void override;

	auto InitPosition_Implementation( //
		int32               Entity,
		FExampleFpsPosition Position
	) -> void override;

	auto UpdatePosition_Implementation( //
		int32               Entity,
		FExampleFpsPosition Position
	) -> void override;

	auto InitToggle_Implementation( //
		int32             Entity,
		FExampleFpsToggle Toggle
	) -> void override;

	auto UpdateToggle_Implementation( //
		int32             Entity,
		FExampleFpsToggle Toggle
	) -> void override;

	auto Push(int32 PlayerId) -> void;
};
