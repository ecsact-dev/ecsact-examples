#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <array>
#include "ecsact/runtime/common.h"
#include "EcsactUnreal/Ecsact.h"
#include "EcsactUnreal/EcsactRunnerSubsystem.h"
#include "EcsactBenchmark.ecsact.hh"
#include "EcsactBenchmark__ecsact__ue.generated.h"


namespace EcsactUnreal::CodegenMeta {
	constexpr auto BenchmarkSystemLikeIds = std::array<ecsact_system_like_id, 1>{
		static_cast<ecsact_system_like_id>(3 /* benchmark.IterateCounter */),
	};
	
	constexpr auto BenchmarkExportNames = std::array<const char*, 1>{
		"benchmark__IterateCounter",
	};
	
}

USTRUCT(BlueprintType)
struct FBenchmarkCounter {
	GENERATED_BODY()
	
	static FBenchmarkCounter FromEcsactComponentData(const void*);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value;
	
};

USTRUCT(BlueprintType)
struct FBenchmarkMassonly {
	GENERATED_BODY()
	
	static FBenchmarkMassonly FromEcsactComponentData(const void*);
	
};

UCLASS(Abstract, Blueprintable, meta = (DisplayName = "Ecsact Runner Package Subsystem (benchmark)"))
class UBenchmarkEcsactRunnerSubsystem : public UEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT
	
	TArray<void(ThisClass::*)(int32, const void*)> InitComponentFns;
	TArray<void(ThisClass::*)(int32, const void*)> UpdateComponentFns;
	TArray<void(ThisClass::*)(int32, const void*)> RemoveComponentFns;
	void RawInitCounter(int32 Entity, const void* Component);
	void RawUpdateCounter(int32 Entity, const void* Component);
	void RawRemoveCounter(int32 Entity, const void* Component);
	void RawInitMassonly(int32 Entity, const void* Component);
	void RawUpdateMassonly(int32 Entity, const void* Component);
	void RawRemoveMassonly(int32 Entity, const void* Component);
	
protected:
	void InitComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	void UpdateComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	void RemoveComponentRaw(ecsact_entity_id, ecsact_component_id, const void*) override;
	
	
public:
	UBenchmarkEcsactRunnerSubsystem();
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init benchmark.Counter"))
	void InitCounter(int32 Entity, FBenchmarkCounter Counter);
	virtual void InitCounter_Implementation(int32 Entity, FBenchmarkCounter Counter);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update benchmark.Counter"))
	void UpdateCounter(int32 Entity, FBenchmarkCounter Counter);
	virtual void UpdateCounter_Implementation(int32 Entity, FBenchmarkCounter Counter);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove benchmark.Counter"))
	void RemoveCounter(int32 Entity, FBenchmarkCounter Counter);
	virtual void RemoveCounter_Implementation(int32 Entity, FBenchmarkCounter Counter);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Init benchmark.MassOnly"))
	void InitMassonly(int32 Entity, FBenchmarkMassonly Massonly);
	virtual void InitMassonly_Implementation(int32 Entity, FBenchmarkMassonly Massonly);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Update benchmark.MassOnly"))
	void UpdateMassonly(int32 Entity, FBenchmarkMassonly Massonly);
	virtual void UpdateMassonly_Implementation(int32 Entity, FBenchmarkMassonly Massonly);
	UFUNCTION(BlueprintNativeEvent, Category = "Ecsact Runner", meta = (DisplayName = "Remove benchmark.MassOnly"))
	void RemoveMassonly(int32 Entity, FBenchmarkMassonly Massonly);
	virtual void RemoveMassonly_Implementation(int32 Entity, FBenchmarkMassonly Massonly);
	
};
