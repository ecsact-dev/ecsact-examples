#pragma once

#include "CoreMinimal.h"

#include "EcsactBenchmark__ecsact__mass__ue.h"
#include "EcsactBenchmark__ecsact__ue.h"

#include "EcsactBenchmarkMassSpawner.generated.h"

UCLASS(Abstract)
class UEcsactBenchmarkMassSpawner : public UOneToOneBenchmarkMassSpawner {
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable)
  void CreateMassEntities(int count, bool UseEcsact);

  UFUNCTION(BlueprintCallable)
  void LoadWASMFiles();

  void InitCounter_Implementation(int32 Entity,
                                  FBenchmarkCounter counter) override;
  void UpdateCounter_Implementation(int32 Entity,
                                    FBenchmarkCounter counter) override;
};
