#pragma once

#include <optional>

#include "CoreMinimal.h"
#include "MassEntityConfigAsset.h"
#include "ecsact/runtime/core.hh"

#include "EcsactBenchmark__ecsact__mass__ue.h"
#include "EcsactBenchmark__ecsact__ue.h"

#include "EcsactBenchmarkMassSpawner.generated.h"

UENUM(BlueprintType)
enum class EcsactBenchmarkType : uint8 {
	EcsactCounter UMETA(DisplayName = "Ecsact Counter"),
	MassCounter   UMETA(DisplayName = "Mass Counter")
};

UCLASS(Abstract)

class UEcsactBenchmarkMassSpawner : public UBenchmarkMassSpawner {
	GENERATED_BODY()
	UEcsactBenchmarkMassSpawner();

	TArray<ecsact_entity_id>  entities;
	TArray<FMassEntityHandle> mass_entities;

	FTimerHandle RunTimer;

	UPROPERTY(EditAnywhere)
	UMassEntityConfigAsset* config;

public:
	UFUNCTION(BlueprintCallable, Meta = (WorldContext = "WorldContext"))
	static void StartMassSpawner(
		UObject*            WorldContext,
		EcsactBenchmarkType BenchmarkType
	);

	UFUNCTION(BlueprintCallable)
	void CreateMassEntities(int count);

	UFUNCTION(BlueprintCallable)
	void CreateEcsactEntities(int count);

	UFUNCTION(BlueprintCallable)
	void LoadWASMFiles();

	UFUNCTION(BlueprintImplementableEvent)
	void OnStartButtonPressed(EcsactBenchmarkType BenchmarkType);

	void InitCounter_Implementation(int32 Entity, FBenchmarkCounter) override;
	void UpdateCounter_Implementation(int32 Entity, FBenchmarkCounter) override;
};
