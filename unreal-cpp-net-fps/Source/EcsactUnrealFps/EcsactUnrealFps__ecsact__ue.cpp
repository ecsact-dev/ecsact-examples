#include "EcsactUnrealFps__ecsact__ue.h"
FExampleFpsPlayer FExampleFpsPlayer::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsPlayer{};
	result.PlayerId = static_cast<const example::fps::Player*>(component_data)->player_id;
	return result;
}
FExampleFpsPusher FExampleFpsPusher::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsPusher{};
	result.CooldownRemaining = static_cast<const example::fps::Pusher*>(component_data)->cooldown_remaining;
	return result;
}
FExampleFpsPusherexpired FExampleFpsPusherexpired::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsPusherexpired{};
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
FExampleFpsStunned FExampleFpsStunned::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsStunned{};
	result.Remaining = static_cast<const example::fps::Stunned*>(component_data)->remaining;
	return result;
}
FExampleFpsStunnedexpired FExampleFpsStunnedexpired::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsStunnedexpired{};
	return result;
}
FExampleFpsPushcharge FExampleFpsPushcharge::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsPushcharge{};
	result.Radius = static_cast<const example::fps::PushCharge*>(component_data)->radius;
	return result;
}
FExampleFpsEnemy FExampleFpsEnemy::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsEnemy{};
	result.PlayerId = static_cast<const example::fps::Enemy*>(component_data)->player_id;
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
FExampleFpsMovedirection FExampleFpsMovedirection::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsMovedirection{};
	result.X = static_cast<const example::fps::MoveDirection*>(component_data)->x;
	result.Y = static_cast<const example::fps::MoveDirection*>(component_data)->y;
	return result;
}
FExampleFpsRemovepushingtag FExampleFpsRemovepushingtag::FromEcsactComponentData(const void* component_data) {
	auto result = FExampleFpsRemovepushingtag{};
	return result;
}
UExampleFpsEcsactRunnerSubsystem::UExampleFpsEcsactRunnerSubsystem() {
	InitComponentFns.Init(nullptr, 24);
	UpdateComponentFns.Init(nullptr, 24);
	RemoveComponentFns.Init(nullptr, 24);
	InitComponentFns[1] = &ThisClass::RawInitPlayer;
	UpdateComponentFns[1] = &ThisClass::RawUpdatePlayer;
	RemoveComponentFns[1] = &ThisClass::RawRemovePlayer;
	InitComponentFns[2] = &ThisClass::RawInitPusher;
	UpdateComponentFns[2] = &ThisClass::RawUpdatePusher;
	RemoveComponentFns[2] = &ThisClass::RawRemovePusher;
	InitComponentFns[3] = &ThisClass::RawInitPusherexpired;
	UpdateComponentFns[3] = &ThisClass::RawUpdatePusherexpired;
	RemoveComponentFns[3] = &ThisClass::RawRemovePusherexpired;
	InitComponentFns[4] = &ThisClass::RawInitRotation;
	UpdateComponentFns[4] = &ThisClass::RawUpdateRotation;
	RemoveComponentFns[4] = &ThisClass::RawRemoveRotation;
	InitComponentFns[5] = &ThisClass::RawInitPosition;
	UpdateComponentFns[5] = &ThisClass::RawUpdatePosition;
	RemoveComponentFns[5] = &ThisClass::RawRemovePosition;
	InitComponentFns[6] = &ThisClass::RawInitStunned;
	UpdateComponentFns[6] = &ThisClass::RawUpdateStunned;
	RemoveComponentFns[6] = &ThisClass::RawRemoveStunned;
	InitComponentFns[7] = &ThisClass::RawInitStunnedexpired;
	UpdateComponentFns[7] = &ThisClass::RawUpdateStunnedexpired;
	RemoveComponentFns[7] = &ThisClass::RawRemoveStunnedexpired;
	InitComponentFns[8] = &ThisClass::RawInitPushcharge;
	UpdateComponentFns[8] = &ThisClass::RawUpdatePushcharge;
	RemoveComponentFns[8] = &ThisClass::RawRemovePushcharge;
	InitComponentFns[9] = &ThisClass::RawInitEnemy;
	UpdateComponentFns[9] = &ThisClass::RawUpdateEnemy;
	RemoveComponentFns[9] = &ThisClass::RawRemoveEnemy;
	InitComponentFns[10] = &ThisClass::RawInitVelocity;
	UpdateComponentFns[10] = &ThisClass::RawUpdateVelocity;
	RemoveComponentFns[10] = &ThisClass::RawRemoveVelocity;
	InitComponentFns[11] = &ThisClass::RawInitPushing;
	UpdateComponentFns[11] = &ThisClass::RawUpdatePushing;
	RemoveComponentFns[11] = &ThisClass::RawRemovePushing;
	InitComponentFns[12] = &ThisClass::RawInitToggle;
	UpdateComponentFns[12] = &ThisClass::RawUpdateToggle;
	RemoveComponentFns[12] = &ThisClass::RawRemoveToggle;
	InitComponentFns[21] = &ThisClass::RawInitMovedirection;
	UpdateComponentFns[21] = &ThisClass::RawUpdateMovedirection;
	RemoveComponentFns[21] = &ThisClass::RawRemoveMovedirection;
	InitComponentFns[23] = &ThisClass::RawInitRemovepushingtag;
	UpdateComponentFns[23] = &ThisClass::RawUpdateRemovepushingtag;
	RemoveComponentFns[23] = &ThisClass::RawRemoveRemovepushingtag;
	
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

void UExampleFpsEcsactRunnerSubsystem::RawInitPlayer(int32 entity, const void* component) {
	InitPlayer(entity, FExampleFpsPlayer::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdatePlayer(int32 entity, const void* component) {
	UpdatePlayer(entity, FExampleFpsPlayer::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemovePlayer(int32 entity, const void* component) {
	RemovePlayer(entity, FExampleFpsPlayer::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawInitPusher(int32 entity, const void* component) {
	InitPusher(entity, FExampleFpsPusher::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdatePusher(int32 entity, const void* component) {
	UpdatePusher(entity, FExampleFpsPusher::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemovePusher(int32 entity, const void* component) {
	RemovePusher(entity, FExampleFpsPusher::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawInitPusherexpired(int32 entity, const void* component) {
	InitPusherexpired(entity, FExampleFpsPusherexpired::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdatePusherexpired(int32 entity, const void* component) {
	UpdatePusherexpired(entity, FExampleFpsPusherexpired::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemovePusherexpired(int32 entity, const void* component) {
	RemovePusherexpired(entity, FExampleFpsPusherexpired::FromEcsactComponentData(component));
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
void UExampleFpsEcsactRunnerSubsystem::RawInitStunned(int32 entity, const void* component) {
	InitStunned(entity, FExampleFpsStunned::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdateStunned(int32 entity, const void* component) {
	UpdateStunned(entity, FExampleFpsStunned::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemoveStunned(int32 entity, const void* component) {
	RemoveStunned(entity, FExampleFpsStunned::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawInitStunnedexpired(int32 entity, const void* component) {
	InitStunnedexpired(entity, FExampleFpsStunnedexpired::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdateStunnedexpired(int32 entity, const void* component) {
	UpdateStunnedexpired(entity, FExampleFpsStunnedexpired::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemoveStunnedexpired(int32 entity, const void* component) {
	RemoveStunnedexpired(entity, FExampleFpsStunnedexpired::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawInitPushcharge(int32 entity, const void* component) {
	InitPushcharge(entity, FExampleFpsPushcharge::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdatePushcharge(int32 entity, const void* component) {
	UpdatePushcharge(entity, FExampleFpsPushcharge::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemovePushcharge(int32 entity, const void* component) {
	RemovePushcharge(entity, FExampleFpsPushcharge::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawInitEnemy(int32 entity, const void* component) {
	InitEnemy(entity, FExampleFpsEnemy::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdateEnemy(int32 entity, const void* component) {
	UpdateEnemy(entity, FExampleFpsEnemy::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemoveEnemy(int32 entity, const void* component) {
	RemoveEnemy(entity, FExampleFpsEnemy::FromEcsactComponentData(component));
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
void UExampleFpsEcsactRunnerSubsystem::RawInitMovedirection(int32 entity, const void* component) {
	InitMovedirection(entity, FExampleFpsMovedirection::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawUpdateMovedirection(int32 entity, const void* component) {
	UpdateMovedirection(entity, FExampleFpsMovedirection::FromEcsactComponentData(component));
}
void UExampleFpsEcsactRunnerSubsystem::RawRemoveMovedirection(int32 entity, const void* component) {
	RemoveMovedirection(entity, FExampleFpsMovedirection::FromEcsactComponentData(component));
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
void UExampleFpsEcsactRunnerSubsystem::InitPlayer_Implementation(int32 Entity, FExampleFpsPlayer Player) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdatePlayer_Implementation(int32 Entity, FExampleFpsPlayer Player) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemovePlayer_Implementation(int32 Entity, FExampleFpsPlayer Player) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitPusher_Implementation(int32 Entity, FExampleFpsPusher Pusher) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdatePusher_Implementation(int32 Entity, FExampleFpsPusher Pusher) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemovePusher_Implementation(int32 Entity, FExampleFpsPusher Pusher) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitPusherexpired_Implementation(int32 Entity, FExampleFpsPusherexpired Pusherexpired) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdatePusherexpired_Implementation(int32 Entity, FExampleFpsPusherexpired Pusherexpired) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemovePusherexpired_Implementation(int32 Entity, FExampleFpsPusherexpired Pusherexpired) {
	
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

void UExampleFpsEcsactRunnerSubsystem::InitStunned_Implementation(int32 Entity, FExampleFpsStunned Stunned) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdateStunned_Implementation(int32 Entity, FExampleFpsStunned Stunned) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemoveStunned_Implementation(int32 Entity, FExampleFpsStunned Stunned) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitStunnedexpired_Implementation(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdateStunnedexpired_Implementation(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemoveStunnedexpired_Implementation(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitPushcharge_Implementation(int32 Entity, FExampleFpsPushcharge Pushcharge) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdatePushcharge_Implementation(int32 Entity, FExampleFpsPushcharge Pushcharge) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemovePushcharge_Implementation(int32 Entity, FExampleFpsPushcharge Pushcharge) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitEnemy_Implementation(int32 Entity, FExampleFpsEnemy Enemy) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdateEnemy_Implementation(int32 Entity, FExampleFpsEnemy Enemy) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemoveEnemy_Implementation(int32 Entity, FExampleFpsEnemy Enemy) {
	
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

void UExampleFpsEcsactRunnerSubsystem::InitMovedirection_Implementation(int32 Entity, FExampleFpsMovedirection Movedirection) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdateMovedirection_Implementation(int32 Entity, FExampleFpsMovedirection Movedirection) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemoveMovedirection_Implementation(int32 Entity, FExampleFpsMovedirection Movedirection) {
	
}

void UExampleFpsEcsactRunnerSubsystem::InitRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag) {
	
}

void UExampleFpsEcsactRunnerSubsystem::UpdateRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag) {
	
}

void UExampleFpsEcsactRunnerSubsystem::RemoveRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag) {
	
}

