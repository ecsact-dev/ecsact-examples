#include "Floppybots__ecsact__ue.h"
FFloppybotsPlayer FFloppybotsPlayer::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsPlayer{};
	result.PlayerId = static_cast<const floppybots::Player*>(component_data)->player_id;
	return result;
}
FFloppybotsPusher FFloppybotsPusher::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsPusher{};
	result.CooldownRemaining = static_cast<const floppybots::Pusher*>(component_data)->cooldown_remaining;
	return result;
}
FFloppybotsPusherexpired FFloppybotsPusherexpired::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsPusherexpired{};
	return result;
}
FFloppybotsRotation FFloppybotsRotation::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsRotation{};
	result.Pitch = static_cast<const floppybots::Rotation*>(component_data)->pitch;
	result.Yaw = static_cast<const floppybots::Rotation*>(component_data)->yaw;
	result.Roll = static_cast<const floppybots::Rotation*>(component_data)->roll;
	return result;
}
FFloppybotsPosition FFloppybotsPosition::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsPosition{};
	result.X = static_cast<const floppybots::Position*>(component_data)->x;
	result.Y = static_cast<const floppybots::Position*>(component_data)->y;
	result.Z = static_cast<const floppybots::Position*>(component_data)->z;
	return result;
}
FFloppybotsStunned FFloppybotsStunned::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsStunned{};
	result.Remaining = static_cast<const floppybots::Stunned*>(component_data)->remaining;
	return result;
}
FFloppybotsStunnedexpired FFloppybotsStunnedexpired::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsStunnedexpired{};
	return result;
}
FFloppybotsPushcharge FFloppybotsPushcharge::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsPushcharge{};
	result.Radius = static_cast<const floppybots::PushCharge*>(component_data)->radius;
	return result;
}
FFloppybotsEnemy FFloppybotsEnemy::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsEnemy{};
	result.PlayerId = static_cast<const floppybots::Enemy*>(component_data)->player_id;
	return result;
}
FFloppybotsVelocity FFloppybotsVelocity::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsVelocity{};
	result.X = static_cast<const floppybots::Velocity*>(component_data)->x;
	result.Y = static_cast<const floppybots::Velocity*>(component_data)->y;
	result.Z = static_cast<const floppybots::Velocity*>(component_data)->z;
	return result;
}
FFloppybotsPushing FFloppybotsPushing::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsPushing{};
	result.TickTotal = static_cast<const floppybots::Pushing*>(component_data)->tick_total;
	result.TickCount = static_cast<const floppybots::Pushing*>(component_data)->tick_count;
	result.MaxHeight = static_cast<const floppybots::Pushing*>(component_data)->max_height;
	result.ForceX = static_cast<const floppybots::Pushing*>(component_data)->force_x;
	result.ForceY = static_cast<const floppybots::Pushing*>(component_data)->force_y;
	result.ForceZ = static_cast<const floppybots::Pushing*>(component_data)->force_z;
	return result;
}
FFloppybotsToggle FFloppybotsToggle::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsToggle{};
	result.Streaming = static_cast<const floppybots::Toggle*>(component_data)->streaming;
	return result;
}
FFloppybotsMovedirection FFloppybotsMovedirection::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsMovedirection{};
	result.X = static_cast<const floppybots::MoveDirection*>(component_data)->x;
	result.Y = static_cast<const floppybots::MoveDirection*>(component_data)->y;
	return result;
}
FFloppybotsRemovepushingtag FFloppybotsRemovepushingtag::FromEcsactComponentData(const void* component_data) {
	auto result = FFloppybotsRemovepushingtag{};
	return result;
}
UFloppybotsEcsactRunnerSubsystem::UFloppybotsEcsactRunnerSubsystem() {
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

void UFloppybotsEcsactRunnerSubsystem::InitComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*InitComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UFloppybotsEcsactRunnerSubsystem::UpdateComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*UpdateComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UFloppybotsEcsactRunnerSubsystem::RemoveComponentRaw( ecsact_entity_id entity, ecsact_component_id component_id, const void* component_data) {
	(this->*RemoveComponentFns[static_cast<int32>(component_id)])(static_cast<int32>(entity), component_data);
}

void UFloppybotsEcsactRunnerSubsystem::RawInitPlayer(int32 entity, const void* component) {
	InitPlayer(entity, FFloppybotsPlayer::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdatePlayer(int32 entity, const void* component) {
	UpdatePlayer(entity, FFloppybotsPlayer::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemovePlayer(int32 entity, const void* component) {
	RemovePlayer(entity, FFloppybotsPlayer::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitPusher(int32 entity, const void* component) {
	InitPusher(entity, FFloppybotsPusher::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdatePusher(int32 entity, const void* component) {
	UpdatePusher(entity, FFloppybotsPusher::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemovePusher(int32 entity, const void* component) {
	RemovePusher(entity, FFloppybotsPusher::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitPusherexpired(int32 entity, const void* component) {
	InitPusherexpired(entity, FFloppybotsPusherexpired::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdatePusherexpired(int32 entity, const void* component) {
	UpdatePusherexpired(entity, FFloppybotsPusherexpired::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemovePusherexpired(int32 entity, const void* component) {
	RemovePusherexpired(entity, FFloppybotsPusherexpired::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitRotation(int32 entity, const void* component) {
	InitRotation(entity, FFloppybotsRotation::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdateRotation(int32 entity, const void* component) {
	UpdateRotation(entity, FFloppybotsRotation::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemoveRotation(int32 entity, const void* component) {
	RemoveRotation(entity, FFloppybotsRotation::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitPosition(int32 entity, const void* component) {
	InitPosition(entity, FFloppybotsPosition::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdatePosition(int32 entity, const void* component) {
	UpdatePosition(entity, FFloppybotsPosition::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemovePosition(int32 entity, const void* component) {
	RemovePosition(entity, FFloppybotsPosition::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitStunned(int32 entity, const void* component) {
	InitStunned(entity, FFloppybotsStunned::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdateStunned(int32 entity, const void* component) {
	UpdateStunned(entity, FFloppybotsStunned::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemoveStunned(int32 entity, const void* component) {
	RemoveStunned(entity, FFloppybotsStunned::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitStunnedexpired(int32 entity, const void* component) {
	InitStunnedexpired(entity, FFloppybotsStunnedexpired::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdateStunnedexpired(int32 entity, const void* component) {
	UpdateStunnedexpired(entity, FFloppybotsStunnedexpired::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemoveStunnedexpired(int32 entity, const void* component) {
	RemoveStunnedexpired(entity, FFloppybotsStunnedexpired::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitPushcharge(int32 entity, const void* component) {
	InitPushcharge(entity, FFloppybotsPushcharge::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdatePushcharge(int32 entity, const void* component) {
	UpdatePushcharge(entity, FFloppybotsPushcharge::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemovePushcharge(int32 entity, const void* component) {
	RemovePushcharge(entity, FFloppybotsPushcharge::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitEnemy(int32 entity, const void* component) {
	InitEnemy(entity, FFloppybotsEnemy::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdateEnemy(int32 entity, const void* component) {
	UpdateEnemy(entity, FFloppybotsEnemy::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemoveEnemy(int32 entity, const void* component) {
	RemoveEnemy(entity, FFloppybotsEnemy::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitVelocity(int32 entity, const void* component) {
	InitVelocity(entity, FFloppybotsVelocity::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdateVelocity(int32 entity, const void* component) {
	UpdateVelocity(entity, FFloppybotsVelocity::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemoveVelocity(int32 entity, const void* component) {
	RemoveVelocity(entity, FFloppybotsVelocity::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitPushing(int32 entity, const void* component) {
	InitPushing(entity, FFloppybotsPushing::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdatePushing(int32 entity, const void* component) {
	UpdatePushing(entity, FFloppybotsPushing::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemovePushing(int32 entity, const void* component) {
	RemovePushing(entity, FFloppybotsPushing::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitToggle(int32 entity, const void* component) {
	InitToggle(entity, FFloppybotsToggle::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdateToggle(int32 entity, const void* component) {
	UpdateToggle(entity, FFloppybotsToggle::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemoveToggle(int32 entity, const void* component) {
	RemoveToggle(entity, FFloppybotsToggle::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitMovedirection(int32 entity, const void* component) {
	InitMovedirection(entity, FFloppybotsMovedirection::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdateMovedirection(int32 entity, const void* component) {
	UpdateMovedirection(entity, FFloppybotsMovedirection::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemoveMovedirection(int32 entity, const void* component) {
	RemoveMovedirection(entity, FFloppybotsMovedirection::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawInitRemovepushingtag(int32 entity, const void* component) {
	InitRemovepushingtag(entity, FFloppybotsRemovepushingtag::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawUpdateRemovepushingtag(int32 entity, const void* component) {
	UpdateRemovepushingtag(entity, FFloppybotsRemovepushingtag::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::RawRemoveRemovepushingtag(int32 entity, const void* component) {
	RemoveRemovepushingtag(entity, FFloppybotsRemovepushingtag::FromEcsactComponentData(component));
}
void UFloppybotsEcsactRunnerSubsystem::InitPlayer_Implementation(int32 Entity, FFloppybotsPlayer Player) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdatePlayer_Implementation(int32 Entity, FFloppybotsPlayer Player) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemovePlayer_Implementation(int32 Entity, FFloppybotsPlayer Player) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitPusher_Implementation(int32 Entity, FFloppybotsPusher Pusher) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdatePusher_Implementation(int32 Entity, FFloppybotsPusher Pusher) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemovePusher_Implementation(int32 Entity, FFloppybotsPusher Pusher) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitPusherexpired_Implementation(int32 Entity, FFloppybotsPusherexpired Pusherexpired) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdatePusherexpired_Implementation(int32 Entity, FFloppybotsPusherexpired Pusherexpired) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemovePusherexpired_Implementation(int32 Entity, FFloppybotsPusherexpired Pusherexpired) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitRotation_Implementation(int32 Entity, FFloppybotsRotation Rotation) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdateRotation_Implementation(int32 Entity, FFloppybotsRotation Rotation) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemoveRotation_Implementation(int32 Entity, FFloppybotsRotation Rotation) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitPosition_Implementation(int32 Entity, FFloppybotsPosition Position) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdatePosition_Implementation(int32 Entity, FFloppybotsPosition Position) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemovePosition_Implementation(int32 Entity, FFloppybotsPosition Position) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitStunned_Implementation(int32 Entity, FFloppybotsStunned Stunned) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdateStunned_Implementation(int32 Entity, FFloppybotsStunned Stunned) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemoveStunned_Implementation(int32 Entity, FFloppybotsStunned Stunned) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitStunnedexpired_Implementation(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdateStunnedexpired_Implementation(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemoveStunnedexpired_Implementation(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitPushcharge_Implementation(int32 Entity, FFloppybotsPushcharge Pushcharge) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdatePushcharge_Implementation(int32 Entity, FFloppybotsPushcharge Pushcharge) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemovePushcharge_Implementation(int32 Entity, FFloppybotsPushcharge Pushcharge) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitEnemy_Implementation(int32 Entity, FFloppybotsEnemy Enemy) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdateEnemy_Implementation(int32 Entity, FFloppybotsEnemy Enemy) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemoveEnemy_Implementation(int32 Entity, FFloppybotsEnemy Enemy) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitVelocity_Implementation(int32 Entity, FFloppybotsVelocity Velocity) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdateVelocity_Implementation(int32 Entity, FFloppybotsVelocity Velocity) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemoveVelocity_Implementation(int32 Entity, FFloppybotsVelocity Velocity) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitPushing_Implementation(int32 Entity, FFloppybotsPushing Pushing) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdatePushing_Implementation(int32 Entity, FFloppybotsPushing Pushing) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemovePushing_Implementation(int32 Entity, FFloppybotsPushing Pushing) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitToggle_Implementation(int32 Entity, FFloppybotsToggle Toggle) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdateToggle_Implementation(int32 Entity, FFloppybotsToggle Toggle) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemoveToggle_Implementation(int32 Entity, FFloppybotsToggle Toggle) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitMovedirection_Implementation(int32 Entity, FFloppybotsMovedirection Movedirection) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdateMovedirection_Implementation(int32 Entity, FFloppybotsMovedirection Movedirection) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemoveMovedirection_Implementation(int32 Entity, FFloppybotsMovedirection Movedirection) {
	
}

void UFloppybotsEcsactRunnerSubsystem::InitRemovepushingtag_Implementation(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag) {
	
}

void UFloppybotsEcsactRunnerSubsystem::UpdateRemovepushingtag_Implementation(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag) {
	
}

void UFloppybotsEcsactRunnerSubsystem::RemoveRemovepushingtag_Implementation(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag) {
	
}

