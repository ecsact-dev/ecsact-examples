#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "MassEntityConfigAsset.h"
#include "ecsact/runtime/common.h"
#include "EcsactBenchmark__ecsact__ue.h"
#include "EcsactBenchmark.ecsact.hh"
#include "EcsactBenchmark__ecsact__mass__ue.generated.h"

USTRUCT()
struct FEcsactEntityFragment : public FMassFragment {
	GENERATED_BODY()
	FEcsactEntityFragment() = default;
	FEcsactEntityFragment(const ecsact_entity_id EntityId) : id(EntityId) {}
	
	ecsact_entity_id GetId() const {
		return id;
		
	}
	private:
	ecsact_entity_id id;
};
USTRUCT()
struct FBenchmarkCounterFragment : public FMassFragment {
	GENERATED_BODY()
	
	FBenchmarkCounterFragment() = default;
	FBenchmarkCounterFragment(FBenchmarkCounter in_component) : component(in_component){}
	
	FBenchmarkCounter component;
};
USTRUCT()
struct FBenchmarkMassonlyFragment : public FMassTag {
	GENERATED_BODY()
	
};

UCLASS(Abstract)
class UBenchmarkMassSpawner : public UBenchmarkEcsactRunnerSubsystem {
	GENERATED_BODY()
	
	public:
	virtual auto GetEcsactMassEntityHandles(int32 Entity) -> TArray<FMassEntityHandle>;
	void InitCounter_Implementation(int32 Entity, FBenchmarkCounter Counter) override;
	void UpdateCounter_Implementation(int32 Entity, FBenchmarkCounter Counter) override;
	void RemoveCounter_Implementation(int32 Entity, FBenchmarkCounter Counter) override;
	void InitMassonly_Implementation(int32 Entity, FBenchmarkMassonly Massonly) override;
	void RemoveMassonly_Implementation(int32 Entity, FBenchmarkMassonly Massonly) override;
	
};

UCLASS(Abstract)
class UOneToOneBenchmarkMassSpawner : public UBenchmarkMassSpawner {
	GENERATED_BODY()
	
	TMap<ecsact_entity_id, TArray<FMassEntityHandle>> MassEntities;
	protected:
	UPROPERTY(EditAnywhere)
	UMassEntityConfigAsset* MassEntityConfigAsset;
	auto EntityCreated_Implementation(int32 Entity) -> void override;
	auto EntityDestroyed_Implementation(int32 Entity) -> void override;
	auto GetEcsactMassEntityHandles(int32 Entity) -> TArray<FMassEntityHandle> override;
	virtual auto GetEntityMassConfig() const -> UMassEntityConfigAsset*;
	
};
