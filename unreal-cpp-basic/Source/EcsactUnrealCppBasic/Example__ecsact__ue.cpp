#include "Example__ecsact__ue.h"
FExamplePosition FExamplePosition::FromEcsactComponentData(const void* component_data) {
	auto result = FExamplePosition{};
	result.X = static_cast<const example::Position*>(component_data)->x;
	result.Y = static_cast<const example::Position*>(component_data)->y;
	result.Z = static_cast<const example::Position*>(component_data)->z;
	return result;
}
FExampleVelocity FExampleVelocity::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleVelocity{};
	result.X = static_cast<const example::Velocity*>(component_data)->x;
	result.Y = static_cast<const example::Velocity*>(component_data)->y;
	result.Z = static_cast<const example::Velocity*>(component_data)->z;
	return result;
}
UExampleEcsactRunnerSubsystem::UExampleEcsactRunnerSubsystem() {
	InitComponentFns.Init(nullptr, 3);
	UpdateComponentFns.Init(nullptr, 3);
	RemoveComponentFns.Init(nullptr, 3);
	InitComponentFns[1] = &ThisClass::RawInitPosition;
	UpdateComponentFns[1] = &ThisClass::RawUpdatePosition;
	RemoveComponentFns[1] = &ThisClass::RawRemovePosition;
	InitComponentFns[2] = &ThisClass::RawInitVelocity;
	UpdateComponentFns[2] = &ThisClass::RawUpdateVelocity;
	RemoveComponentFns[2] = &ThisClass::RawRemoveVelocity;
	
}

void UExampleEcsactRunnerSubsystem::InitComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*InitComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UExampleEcsactRunnerSubsystem::UpdateComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*UpdateComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UExampleEcsactRunnerSubsystem::RemoveComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*RemoveComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UExampleEcsactRunnerSubsystem::RawInitPosition(int32 entity, const void* component) {
	InitPosition(entity, FExamplePosition::FromEcsactComponentData(component));
}
void UExampleEcsactRunnerSubsystem::RawUpdatePosition(int32 entity, const void* component) {
	UpdatePosition(entity, FExamplePosition::FromEcsactComponentData(component));
}
void UExampleEcsactRunnerSubsystem::RawRemovePosition(int32 entity, const void* component) {
	RemovePosition(entity, FExamplePosition::FromEcsactComponentData(component));
}
void UExampleEcsactRunnerSubsystem::RawInitVelocity(int32 entity, const void* component) {
	InitVelocity(entity, FExampleVelocity::FromEcsactComponentData(component));
}
void UExampleEcsactRunnerSubsystem::RawUpdateVelocity(int32 entity, const void* component) {
	UpdateVelocity(entity, FExampleVelocity::FromEcsactComponentData(component));
}
void UExampleEcsactRunnerSubsystem::RawRemoveVelocity(int32 entity, const void* component) {
	RemoveVelocity(entity, FExampleVelocity::FromEcsactComponentData(component));
}
void UExampleEcsactRunnerSubsystem::InitPosition_Implementation(int32 Entity, FExamplePosition Position) {
	
}

void UExampleEcsactRunnerSubsystem::UpdatePosition_Implementation(int32 Entity, FExamplePosition Position) {
	
}

void UExampleEcsactRunnerSubsystem::RemovePosition_Implementation(int32 Entity, FExamplePosition Position) {
	
}

void UExampleEcsactRunnerSubsystem::InitVelocity_Implementation(int32 Entity, FExampleVelocity Velocity) {
	
}

void UExampleEcsactRunnerSubsystem::UpdateVelocity_Implementation(int32 Entity, FExampleVelocity Velocity) {
	
}

void UExampleEcsactRunnerSubsystem::RemoveVelocity_Implementation(int32 Entity, FExampleVelocity Velocity) {
	
}

