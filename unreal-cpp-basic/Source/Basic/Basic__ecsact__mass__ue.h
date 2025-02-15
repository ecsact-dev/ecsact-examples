#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "MassEntityConfigAsset.h"
#include "ecsact/runtime/common.h"
#include "Basic__ecsact__ue.h"
#include "Basic.ecsact.hh"
#include "Basic__ecsact__mass__ue.generated.h"


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
struct FBasicCountFragment : public FMassFragment {
	GENERATED_BODY()
	
	FBasicCountFragment() = default;
	FBasicCountFragment(FBasicCount in_component) : component(in_component){}
	
	FBasicCount component;
};


UCLASS(Abstract)
class UBasicMassSpawner : public UBasicEcsactRunnerSubsystem {
	GENERATED_BODY()
	
	public:
	virtual auto GetEcsactMassEntityHandles(int32 Entity) -> TArray<FMassEntityHandle>;
	void InitCount_Implementation(int32 Entity, FBasicCount Count) override;
	void UpdateCount_Implementation(int32 Entity, FBasicCount Count) override;
	void RemoveCount_Implementation(int32 Entity, FBasicCount Count) override;
	
};


UCLASS(Abstract)
class UOneToOneBasicMassSpawner : public UBasicMassSpawner {
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
