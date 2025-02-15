#include "Basic__ecsact__ue.h"
FBasicCount FBasicCount::FromEcsactComponentData(const void* component_data) {
	auto result = FBasicCount{};
	result.Value = static_cast<const basic::Count*>(component_data)->value;
	return result;
}
UBasicEcsactRunnerSubsystem::UBasicEcsactRunnerSubsystem() {
	InitComponentFns.Init(nullptr, 2);
	UpdateComponentFns.Init(nullptr, 2);
	RemoveComponentFns.Init(nullptr, 2);
	InitComponentFns[1] = &ThisClass::RawInitCount;
	UpdateComponentFns[1] = &ThisClass::RawUpdateCount;
	RemoveComponentFns[1] = &ThisClass::RawRemoveCount;
	
}

void UBasicEcsactRunnerSubsystem::InitComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*InitComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UBasicEcsactRunnerSubsystem::UpdateComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*UpdateComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UBasicEcsactRunnerSubsystem::RemoveComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*RemoveComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UBasicEcsactRunnerSubsystem::RawInitCount(int32 entity, const void* component) {
	InitCount(entity, FBasicCount::FromEcsactComponentData(component));
}
void UBasicEcsactRunnerSubsystem::RawUpdateCount(int32 entity, const void* component) {
	UpdateCount(entity, FBasicCount::FromEcsactComponentData(component));
}
void UBasicEcsactRunnerSubsystem::RawRemoveCount(int32 entity, const void* component) {
	RemoveCount(entity, FBasicCount::FromEcsactComponentData(component));
}
void UBasicEcsactRunnerSubsystem::InitCount_Implementation(int32 Entity, FBasicCount Count) {
	
}

void UBasicEcsactRunnerSubsystem::UpdateCount_Implementation(int32 Entity, FBasicCount Count) {
	
}

void UBasicEcsactRunnerSubsystem::RemoveCount_Implementation(int32 Entity, FBasicCount Count) {
	
}

