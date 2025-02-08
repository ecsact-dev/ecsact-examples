
#pragma once

#include <tuple>
#include <optional>

#include "CoreMinimal.h"

#include "MassEntityConfigAsset.h"
#include "Floppybots__ecsact__ue.h"
#include "Floppybots__ecsact__mass__ue.h"
#include "MassEntitySpawnDataGeneratorBase.h"
#include "EcsactEntityMassSpawner.generated.h"

UCLASS(Abstract)

class UEcsactEntityMassSpawner : public UOneToOneFloppybotsMassSpawner {
	GENERATED_BODY() // NOLINT

	/**
	 * Entity Mass config used when Ecsact entity streaming is enabled.
	 */
	UPROPERTY(EditAnywhere)
	UMassEntityConfigAsset* StreamingMassEntityConfigAsset;

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

	UMassEntityConfigAsset* GetEntityMassConfig() const override;

	auto ToggleStreamTag(int32 Entity, FFloppybotsToggle Toggle) -> void;

	auto InitEnemy_Implementation( //
		int32            Entity,
		FFloppybotsEnemy Enemy
	) -> void override;

	auto UpdateEnemy_Implementation( //
		int32            Entity,
		FFloppybotsEnemy Enemy
	) -> void override;

	auto RemoveEnemy_Implementation( //
		int32            Entity,
		FFloppybotsEnemy Enemy
	) -> void override;

	auto InitPosition_Implementation( //
		int32               Entity,
		FFloppybotsPosition Position
	) -> void override;

	auto InitRotation_Implementation( //
		int32               Entity,
		FFloppybotsRotation Rotation
	) -> void override;

	auto InitToggle_Implementation( //
		int32             Entity,
		FFloppybotsToggle Toggle
	) -> void override;

	auto UpdateToggle_Implementation( //
		int32             Entity,
		FFloppybotsToggle Toggle
	) -> void override;

	auto InitStunned_Implementation( //
		int32              Entity,
		FFloppybotsStunned Stunned
	) -> void override;

	auto UpdateStunned_Implementation( //
		int32              Entity,
		FFloppybotsStunned Stunned
	) -> void override;

	auto RemoveStunned_Implementation( //
		int32              Entity,
		FFloppybotsStunned Stunned
	) -> void override;

	auto InitPushing_Implementation( //
		int32              Entity,
		FFloppybotsPushing Pushing
	) -> void override;
};
