
#pragma once

#include "CoreMinimal.h"
#include "MassEntityConfigAsset.h"
#include "EcsactUnrealFps__ecsact__ue.h"
#include "MassEntitySpawnDataGeneratorBase.h"
#include "MassEntityTypes.h"
#include "Ecsact/runtime/common.h"
#include "EcsactEntityMassSpawner.generated.h"

UCLASS()

class UEcsactEntityMassSpawner : public UExampleFpsEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT

	UPROPERTY(EditAnywhere)
	UMassEntityConfigAsset* MassEntityConfigAsset;

	UPROPERTY(EditAnywhere)
	TArray<UMassEntitySpawnDataGeneratorBase*> SpawnDataGenerators;

	TMap<ecsact_entity_id, FMassEntityHandle> MassEntities;

	TArray<FMassEntityHandle> EntityHandles;

public:
	UFUNCTION(BlueprintCallable)
	void CreateMassEntities(int count);

	auto InitMassentity_Implementation( //
		int32                 Entity,
		FExampleFpsMassentity MassEntity
	) -> void override;
};
