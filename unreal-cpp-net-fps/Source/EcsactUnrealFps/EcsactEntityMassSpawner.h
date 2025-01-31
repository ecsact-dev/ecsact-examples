
#pragma once

#include <tuple>
#include <optional>

#include "CoreMinimal.h"
#pragma once

#include "MassEntityConfigAsset.h"
#include "EcsactUnrealFps__ecsact__ue.h"
#include "EcsactUnrealFps__ecsact__mass__ue.h"
#include "MassEntitySpawnDataGeneratorBase.h"
#include "MassEntityTypes.h"
#include "Ecsact/runtime/common.h"
#include "EcsactEntityMassSpawner.generated.h"

UCLASS(Abstract)

// TODO(Kelwan): MassSpawner does more than its name implies and should be
// separated before merging to main
class UEcsactEntityMassSpawner : public UOneToOneExampleFpsMassSpawner {
	GENERATED_BODY() // NOLINT
									 //

	/**
	 * Entity Mass config used when Ecsact entity streaming is enabled.
	 */
	UPROPERTY(EditAnywhere)
	UMassEntityConfigAsset* StreamingMassEntityConfigAsset;

	auto CheckMassEntities(int32 Entity, const TCHAR* EventName) -> bool;

	UPROPERTY()
	bool StreamEntities;

public:
	UEcsactEntityMassSpawner();

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

	UMassEntityConfigAsset* GetEntityMassConfig() const override;

	auto EntityCreated_Implementation(int32 Entity) -> void override;

	auto InitEnemy_Implementation( //
		int32            Entity,
		FExampleFpsEnemy Enemy
	) -> void override;

	auto UpdateEnemy_Implementation( //
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

	auto InitRotation_Implementation( //
		int32               Entity,
		FExampleFpsRotation Rotation
	) -> void override;

	auto UpdateToggle_Implementation( //
		int32             Entity,
		FExampleFpsToggle Toggle
	) -> void override;

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
	) -> void override;

	auto InitPushing_Implementation( //
		int32              Entity,
		FExampleFpsPushing Pushing
	) -> void override;
};
