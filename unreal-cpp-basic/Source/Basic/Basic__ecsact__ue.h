#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <array>
#include "ecsact/runtime/common.h"
#include "EcsactUnreal/Ecsact.h"
#include "EcsactUnreal/EcsactRunnerSubsystem.h"
#include "Basic.ecsact.hh"
#include "Basic__ecsact__ue.generated.h"


namespace EcsactUnreal::CodegenMeta {
	constexpr auto BasicSystemLikeIds = std::array<ecsact_system_like_id, 1>{
		static_cast<ecsact_system_like_id>(2 /* basic.Counter */),
	};
	
	constexpr auto BasicExportNames = std::array<const char*, 1>{
		"basic__Counter",
	};
	
}


USTRUCT(BlueprintType)
struct FBasicCount {
	GENERATED_BODY()
	
	static FBasicCount FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value;
	
};


UCLASS(Abstract, Blueprintable, meta = (DisplayName = "Ecsact Runner Package Subsystem (basic)"))
class UBasicEcsactRunnerSubsystem : public UEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT
	
	TArray<void(ThisClass::*)(int32, const void*)> InitComponentFns;
	TArray<void(ThisClass::*)(int32, const void*)> UpdateComponentFns;
	TArray<void(ThisClass::*)(int32, const void*)> RemoveComponentFns;
	void RawInitCount(int32 Entity, const void* Component);
	void RawUpdateCount(int32 Entity, const void* Component);
	void RawRemoveCount(int32 Entity, const void* Component);
	
protected:
	void InitComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	void UpdateComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	void RemoveComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	
	
public:
	UBasicEcsactRunnerSubsystem();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init basic.Count"))
	void InitCount(int32 Entity, FBasicCount Count);
	virtual void InitCount_Implementation(int32 Entity, FBasicCount Count);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update basic.Count"))
	void UpdateCount(int32 Entity, FBasicCount Count);
	virtual void UpdateCount_Implementation(int32 Entity, FBasicCount Count);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove basic.Count"))
	void RemoveCount(int32 Entity, FBasicCount Count);
	virtual void RemoveCount_Implementation(int32 Entity, FBasicCount Count);
	
};
