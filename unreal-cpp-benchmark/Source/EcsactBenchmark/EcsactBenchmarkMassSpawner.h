#pragma once

#include <optional>
#include <string>

#include "CoreMinimal.h"
#include "MassEntityConfigAsset.h"
#include "ecsact/runtime/core.hh"

#include "EcsactBenchmark__ecsact__mass__ue.h"
#include "EcsactBenchmark__ecsact__ue.h"

#include "EcsactBenchmarkMassSpawner.generated.h"

UENUM(BlueprintType)
enum class EcsactBenchmarkType : uint8 {
  EcsactCounter UMETA(DisplayName = "Ecsact Counter"),
  MassCounter UMETA(DisplayName = "Mass Counter")
};

UCLASS(Abstract)
class UEcsactBenchmarkMassSpawner : public UBenchmarkMassSpawner {
  GENERATED_BODY()
  UEcsactBenchmarkMassSpawner();

  std::optional<ecsact::core::registry> registry;
  std::optional<ecsact::core::execution_events_collector<>> evc;

  TArray<ecsact_entity_id> entities;
  TArray<FMassEntityHandle> mass_entities;

  UPROPERTY(EditAnywhere)
  UMassEntityConfigAsset *config;

public:
  UFUNCTION(BlueprintCallable, Meta = (WorldContext = "WorldContext"))
  static void StartMassSpawner(UObject *WorldContext,
                               EcsactBenchmarkType BenchmarkType);

  UFUNCTION(BlueprintCallable)
  void CreateMassEntities(int count);

  UFUNCTION(BlueprintCallable)
  void CreateEcsactEntities(int count);

  UFUNCTION(BlueprintCallable)
  void LoadWASMFiles();

  UFUNCTION(BlueprintCallable)
  void ExecuteSystems(int count);

  void InitCounter(ecsact_entity_id Entity, const benchmark::Counter &Counter);
  void UpdateCounter(ecsact_entity_id Entity,
                     const benchmark::Counter &Counter);

  UFUNCTION(BlueprintImplementableEvent)
  void OnStartButtonPressed(EcsactBenchmarkType BenchmarkType);
};
