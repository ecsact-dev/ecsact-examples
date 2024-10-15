#include "EcsactUnrealFps__ecsact__ue.h"
FExampleFpsProjectile FExampleFpsProjectile::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsProjectile{};
	return result;
}
FExampleFpsPlayer FExampleFpsPlayer::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsPlayer{};
	result.PlayerId = static_cast<const example::fps::Player*>(component_data)->player_id;
	return result;
}
FExampleFpsRotation FExampleFpsRotation::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsRotation{};
	result.Pitch = static_cast<const example::fps::Rotation*>(component_data)->pitch;
	result.Yaw = static_cast<const example::fps::Rotation*>(component_data)->yaw;
	result.Roll = static_cast<const example::fps::Rotation*>(component_data)->roll;
	return result;
}
FExampleFpsPosition FExampleFpsPosition::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsPosition{};
	result.X = static_cast<const example::fps::Position*>(component_data)->x;
	result.Y = static_cast<const example::fps::Position*>(component_data)->y;
	result.Z = static_cast<const example::fps::Position*>(component_data)->z;
	return result;
}
UExampleFpsEcsactRunnerSubsystem::UExampleFpsEcsactRunnerSubsystem() {
	InitComponentFns.Init(nullptr, 5);
	UpdateComponentFns.Init(nullptr, 5);
	RemoveComponentFns.Init(nullptr, 5);
	InitComponentFns[1] = &ThisClass::RawInitProjectile;
	UpdateComponentFns[1] = &ThisClass::RawUpdateProjectile;
	RemoveComponentFns[1] = &ThisClass::RawRemoveProjectile;
	InitComponentFns[2] = &ThisClass::RawInitPlayer;
	UpdateComponentFns[2] = &ThisClass::RawUpdatePlayer;
	RemoveComponentFns[2] = &ThisClass::RawRemovePlayer;
	InitComponentFns[3] = &ThisClass::RawInitRotation;
	UpdateComponentFns[3] = &ThisClass::RawUpdateRotation;
	RemoveComponentFns[3] = &ThisClass::RawRemoveRotation;
	InitComponentFns[4] = &ThisClass::RawInitPosition;
	UpdateComponentFns[4] = &ThisClass::RawUpdatePosition;
	RemoveComponentFns[4] = &ThisClass::RawRemovePosition;
	
}

void UExampleFpsEcsactRunnerSubsystem::InitComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*InitComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UExampleFpsEcsactRunnerSubsystem::UpdateComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*UpdateComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UExampleFpsEcsactRunnerSubsystem::RemoveComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*RemoveComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UExampleFpsEcsactRunnerSubsystem::RawInitProjectile(int32 entity, const void* component) {
	InitProjectile(entity, FExampleFpsProjectile::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdateProjectile(int32 entity, const void* component) {
	UpdateProjectile(entity, FExampleFpsProjectile::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemoveProjectile(int32 entity, const void* component) {
	RemoveProjectile(entity, FExampleFpsProjectile::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawInitPlayer(int32 entity, const void* component) {
	InitPlayer(entity, FExampleFpsPlayer::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdatePlayer(int32 entity, const void* component) {
	UpdatePlayer(entity, FExampleFpsPlayer::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemovePlayer(int32 entity, const void* component) {
	RemovePlayer(entity, FExampleFpsPlayer::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawInitRotation(int32 entity, const void* component) {
	InitRotation(entity, FExampleFpsRotation::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdateRotation(int32 entity, const void* component) {
	UpdateRotation(entity, FExampleFpsRotation::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemoveRotation(int32 entity, const void* component) {
	RemoveRotation(entity, FExampleFpsRotation::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawInitPosition(int32 entity, const void* component) {
	InitPosition(entity, FExampleFpsPosition::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdatePosition(int32 entity, const void* component) {
	UpdatePosition(entity, FExampleFpsPosition::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemovePosition(int32 entity, const void* component) {
	RemovePosition(entity, FExampleFpsPosition::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::InitProjectile_Implementation(int32 Entity, FExampleFpsProjectile Projectile) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdateProjectile_Implementation(int32 Entity, FExampleFpsProjectile Projectile) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemoveProjectile_Implementation(int32 Entity, FExampleFpsProjectile Projectile) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitPlayer_Implementation(int32 Entity, FExampleFpsPlayer Player) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdatePlayer_Implementation(int32 Entity, FExampleFpsPlayer Player) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemovePlayer_Implementation(int32 Entity, FExampleFpsPlayer Player) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitRotation_Implementation(int32 Entity, FExampleFpsRotation Rotation) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdateRotation_Implementation(int32 Entity, FExampleFpsRotation Rotation) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemoveRotation_Implementation(int32 Entity, FExampleFpsRotation Rotation) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitPosition_Implementation(int32 Entity, FExampleFpsPosition Position) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdatePosition_Implementation(int32 Entity, FExampleFpsPosition Position) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemovePosition_Implementation(int32 Entity, FExampleFpsPosition Position) {
	
}

