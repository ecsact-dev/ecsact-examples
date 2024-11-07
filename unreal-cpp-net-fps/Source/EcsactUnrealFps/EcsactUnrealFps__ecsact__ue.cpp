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
FExampleFpsMassentity FExampleFpsMassentity::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsMassentity{};
	return result;
}
FExampleFpsVelocity FExampleFpsVelocity::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsVelocity{};
	result.X = static_cast<const example::fps::Velocity*>(component_data)->x;
	result.Y = static_cast<const example::fps::Velocity*>(component_data)->y;
	result.Z = static_cast<const example::fps::Velocity*>(component_data)->z;
	return result;
}
FExampleFpsPushing FExampleFpsPushing::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsPushing{};
	result.TickCount = static_cast<const example::fps::Pushing*>(component_data)->tick_count;
	result.ForceX = static_cast<const example::fps::Pushing*>(component_data)->force_x;
	result.ForceY = static_cast<const example::fps::Pushing*>(component_data)->force_y;
	result.ForceZ = static_cast<const example::fps::Pushing*>(component_data)->force_z;
	return result;
}
FExampleFpsToggle FExampleFpsToggle::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsToggle{};
	result.Streaming = static_cast<const example::fps::Toggle*>(component_data)->streaming;
	return result;
}
FExampleFpsRemovepushingtag FExampleFpsRemovepushingtag::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsRemovepushingtag{};
	return result;
}
UExampleFpsEcsactRunnerSubsystem::UExampleFpsEcsactRunnerSubsystem() {
	InitComponentFns.Init(nullptr, 15);
	UpdateComponentFns.Init(nullptr, 15);
	RemoveComponentFns.Init(nullptr, 15);
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
	InitComponentFns[5] = &ThisClass::RawInitMassentity;
	UpdateComponentFns[5] = &ThisClass::RawUpdateMassentity;
	RemoveComponentFns[5] = &ThisClass::RawRemoveMassentity;
	InitComponentFns[8] = &ThisClass::RawInitVelocity;
	UpdateComponentFns[8] = &ThisClass::RawUpdateVelocity;
	RemoveComponentFns[8] = &ThisClass::RawRemoveVelocity;
	InitComponentFns[9] = &ThisClass::RawInitPushing;
	UpdateComponentFns[9] = &ThisClass::RawUpdatePushing;
	RemoveComponentFns[9] = &ThisClass::RawRemovePushing;
	InitComponentFns[10] = &ThisClass::RawInitToggle;
	UpdateComponentFns[10] = &ThisClass::RawUpdateToggle;
	RemoveComponentFns[10] = &ThisClass::RawRemoveToggle;
	InitComponentFns[14] = &ThisClass::RawInitRemovepushingtag;
	UpdateComponentFns[14] = &ThisClass::RawUpdateRemovepushingtag;
	RemoveComponentFns[14] = &ThisClass::RawRemoveRemovepushingtag;
	
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
void UExampleFpsEcsactRunnerSubsystem::RawInitMassentity(int32 entity, const void* component) {
	InitMassentity(entity, FExampleFpsMassentity::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdateMassentity(int32 entity, const void* component) {
	UpdateMassentity(entity, FExampleFpsMassentity::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemoveMassentity(int32 entity, const void* component) {
	RemoveMassentity(entity, FExampleFpsMassentity::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawInitVelocity(int32 entity, const void* component) {
	InitVelocity(entity, FExampleFpsVelocity::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdateVelocity(int32 entity, const void* component) {
	UpdateVelocity(entity, FExampleFpsVelocity::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemoveVelocity(int32 entity, const void* component) {
	RemoveVelocity(entity, FExampleFpsVelocity::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawInitPushing(int32 entity, const void* component) {
	InitPushing(entity, FExampleFpsPushing::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdatePushing(int32 entity, const void* component) {
	UpdatePushing(entity, FExampleFpsPushing::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemovePushing(int32 entity, const void* component) {
	RemovePushing(entity, FExampleFpsPushing::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawInitToggle(int32 entity, const void* component) {
	InitToggle(entity, FExampleFpsToggle::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdateToggle(int32 entity, const void* component) {
	UpdateToggle(entity, FExampleFpsToggle::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemoveToggle(int32 entity, const void* component) {
	RemoveToggle(entity, FExampleFpsToggle::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawInitRemovepushingtag(int32 entity, const void* component) {
	InitRemovepushingtag(entity, FExampleFpsRemovepushingtag::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdateRemovepushingtag(int32 entity, const void* component) {
	UpdateRemovepushingtag(entity, FExampleFpsRemovepushingtag::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemoveRemovepushingtag(int32 entity, const void* component) {
	RemoveRemovepushingtag(entity, FExampleFpsRemovepushingtag::FromEcsactComponentData(component));
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

void UExampleFpsEcsactRunnerSubsystem::InitMassentity_Implementation(int32 Entity, FExampleFpsMassentity Massentity) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdateMassentity_Implementation(int32 Entity, FExampleFpsMassentity Massentity) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemoveMassentity_Implementation(int32 Entity, FExampleFpsMassentity Massentity) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitVelocity_Implementation(int32 Entity, FExampleFpsVelocity Velocity) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdateVelocity_Implementation(int32 Entity, FExampleFpsVelocity Velocity) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemoveVelocity_Implementation(int32 Entity, FExampleFpsVelocity Velocity) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitPushing_Implementation(int32 Entity, FExampleFpsPushing Pushing) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdatePushing_Implementation(int32 Entity, FExampleFpsPushing Pushing) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemovePushing_Implementation(int32 Entity, FExampleFpsPushing Pushing) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitToggle_Implementation(int32 Entity, FExampleFpsToggle Toggle) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdateToggle_Implementation(int32 Entity, FExampleFpsToggle Toggle) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemoveToggle_Implementation(int32 Entity, FExampleFpsToggle Toggle) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdateRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemoveRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag) {
	
}

