
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

	UPROPERTY()
	bool StreamEntities;

public:
	UFUNCTION(BlueprintCallable) void CreateMassEntities(int count);

	UFUNCTION(
		BlueprintCallable,
		Category = "Ecsact Net Unreal Example",
		Meta = (WorldContext = "WorldContext")
	)
	static void SetStreamEntities(
		const UObject* WorldContext,
		bool           bStreamEntities
	);

	UFUNCTION(
		BlueprintCallable,
		Category = "Ecsact Net Unreal Example",
		Meta = (WorldContext = "WorldContext")
	)
	static bool IsStreamingEntities(const UObject* WorldContext);

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

<<<<<<< HEAD
	auto InitStunned_Implementation( //
		int32              Entity,
		FExampleFpsStunned Stunned
	) -> void override;

	auto UpdateStunned_Implementation( //
		int32              Entity,
		FExampleFpsStunned Stunned
	) -> void override;

	auto RemoveStunned_Implementation( //
		int32              Entity,
		FExampleFpsStunned Stunned
=======
	auto InitPushing_Implementation( //
		int32              Entity,
		FExampleFpsPushing Pushing
	) -> void override;

	auto RemovePushing_Implementation( //
		int32              Entity,
		FExampleFpsPushing Pushing
>>>>>>> 34e45b0 (feat: Physics on entities)
	) -> void override;
};
