#include "EcsactBenchmark__ecsact__ue.h"
FBenchmarkCounter FBenchmarkCounter::FromEcsactComponentData(const void* component_data) {
	auto result = FBenchmarkCounter{};
	result.Value = static_cast<const benchmark::Counter*>(component_data)->value;
	return result;
}
FBenchmarkMassonly FBenchmarkMassonly::FromEcsactComponentData(const void* component_data) {
	auto result = FBenchmarkMassonly{};
	return result;
}
UBenchmarkEcsactRunnerSubsystem::UBenchmarkEcsactRunnerSubsystem() {
	InitComponentFns.Init(nullptr, 3);
	UpdateComponentFns.Init(nullptr, 3);
	RemoveComponentFns.Init(nullptr, 3);
	InitComponentFns[1] = &ThisClass::RawInitCounter;
	UpdateComponentFns[1] = &ThisClass::RawUpdateCounter;
	RemoveComponentFns[1] = &ThisClass::RawRemoveCounter;
	InitComponentFns[2] = &ThisClass::RawInitMassonly;
	UpdateComponentFns[2] = &ThisClass::RawUpdateMassonly;
	RemoveComponentFns[2] = &ThisClass::RawRemoveMassonly;
	
}

void UBenchmarkEcsactRunnerSubsystem::InitComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*InitComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UBenchmarkEcsactRunnerSubsystem::UpdateComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*UpdateComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UBenchmarkEcsactRunnerSubsystem::RemoveComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*RemoveComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UBenchmarkEcsactRunnerSubsystem::RawInitCounter(int32 entity, const void* component) {
	InitCounter(entity, FBenchmarkCounter::FromEcsactComponentData(component));
}
void UBenchmarkEcsactRunnerSubsystem::RawUpdateCounter(int32 entity, const void* component) {
	UpdateCounter(entity, FBenchmarkCounter::FromEcsactComponentData(component));
}
void UBenchmarkEcsactRunnerSubsystem::RawRemoveCounter(int32 entity, const void* component) {
	RemoveCounter(entity, FBenchmarkCounter::FromEcsactComponentData(component));
}
void UBenchmarkEcsactRunnerSubsystem::RawInitMassonly(int32 entity, const void* component) {
	InitMassonly(entity, FBenchmarkMassonly::FromEcsactComponentData(component));
}
void UBenchmarkEcsactRunnerSubsystem::RawUpdateMassonly(int32 entity, const void* component) {
	UpdateMassonly(entity, FBenchmarkMassonly::FromEcsactComponentData(component));
}
void UBenchmarkEcsactRunnerSubsystem::RawRemoveMassonly(int32 entity, const void* component) {
	RemoveMassonly(entity, FBenchmarkMassonly::FromEcsactComponentData(component));
}
void UBenchmarkEcsactRunnerSubsystem::InitCounter_Implementation(int32 Entity, FBenchmarkCounter Counter) {
	
}

void UBenchmarkEcsactRunnerSubsystem::UpdateCounter_Implementation(int32 Entity, FBenchmarkCounter Counter) {
	
}

void UBenchmarkEcsactRunnerSubsystem::RemoveCounter_Implementation(int32 Entity, FBenchmarkCounter Counter) {
	
}

void UBenchmarkEcsactRunnerSubsystem::InitMassonly_Implementation(int32 Entity, FBenchmarkMassonly Massonly) {
	
}

void UBenchmarkEcsactRunnerSubsystem::UpdateMassonly_Implementation(int32 Entity, FBenchmarkMassonly Massonly) {
	
}

void UBenchmarkEcsactRunnerSubsystem::RemoveMassonly_Implementation(int32 Entity, FBenchmarkMassonly Massonly) {
	
}

