#include "Floppybots__ecsact__mass__ue.h"
#include "Engine/World.h"
#include "MassEntitySubsystem.h"
#include "MassSpawnerSubsystem.h"
#include "MassCommandBuffer.h"

void UFloppybotsMassSpawner::InitPlayer_Implementation(int32 Entity, FFloppybotsPlayer Player) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FFloppybotsPlayerFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FFloppybotsPlayerFragment{ Player });
	}
}
void UFloppybotsMassSpawner::UpdatePlayer_Implementation(int32 Entity, FFloppybotsPlayer Player) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Player](FMassEntityManager& entity_manager) {
			auto fragment = entity_manager.GetFragmentDataPtr<FFloppybotsPlayerFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FFloppybotsPlayerFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Player;
		});
	}
}
void UFloppybotsMassSpawner::RemovePlayer_Implementation(int32 Entity, FFloppybotsPlayer Player) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FFloppybotsPlayerFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitPusher_Implementation(int32 Entity, FFloppybotsPusher Pusher) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FFloppybotsPusherFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FFloppybotsPusherFragment{ Pusher });
	}
}
void UFloppybotsMassSpawner::UpdatePusher_Implementation(int32 Entity, FFloppybotsPusher Pusher) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Pusher](FMassEntityManager& entity_manager) {
			auto fragment = entity_manager.GetFragmentDataPtr<FFloppybotsPusherFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FFloppybotsPusherFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Pusher;
		});
	}
}
void UFloppybotsMassSpawner::RemovePusher_Implementation(int32 Entity, FFloppybotsPusher Pusher) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FFloppybotsPusherFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitPusherexpired_Implementation(int32 Entity, FFloppybotsPusherexpired Pusherexpired) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddTag<FFloppybotsPusherexpiredFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::RemovePusherexpired_Implementation(int32 Entity, FFloppybotsPusherexpired Pusherexpired) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveTag<FFloppybotsPusherexpiredFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitRotation_Implementation(int32 Entity, FFloppybotsRotation Rotation) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FFloppybotsRotationFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FFloppybotsRotationFragment{ Rotation });
	}
}
void UFloppybotsMassSpawner::UpdateRotation_Implementation(int32 Entity, FFloppybotsRotation Rotation) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Rotation](FMassEntityManager& entity_manager) {
			auto fragment = entity_manager.GetFragmentDataPtr<FFloppybotsRotationFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FFloppybotsRotationFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Rotation;
		});
	}
}
void UFloppybotsMassSpawner::RemoveRotation_Implementation(int32 Entity, FFloppybotsRotation Rotation) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FFloppybotsRotationFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitPosition_Implementation(int32 Entity, FFloppybotsPosition Position) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FFloppybotsPositionFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FFloppybotsPositionFragment{ Position });
	}
}
void UFloppybotsMassSpawner::UpdatePosition_Implementation(int32 Entity, FFloppybotsPosition Position) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Position](FMassEntityManager& entity_manager) {
			auto fragment = entity_manager.GetFragmentDataPtr<FFloppybotsPositionFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FFloppybotsPositionFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Position;
		});
	}
}
void UFloppybotsMassSpawner::RemovePosition_Implementation(int32 Entity, FFloppybotsPosition Position) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FFloppybotsPositionFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitStunned_Implementation(int32 Entity, FFloppybotsStunned Stunned) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FFloppybotsStunnedFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FFloppybotsStunnedFragment{ Stunned });
	}
}
void UFloppybotsMassSpawner::UpdateStunned_Implementation(int32 Entity, FFloppybotsStunned Stunned) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Stunned](FMassEntityManager& entity_manager) {
			auto fragment = entity_manager.GetFragmentDataPtr<FFloppybotsStunnedFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FFloppybotsStunnedFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Stunned;
		});
	}
}
void UFloppybotsMassSpawner::RemoveStunned_Implementation(int32 Entity, FFloppybotsStunned Stunned) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FFloppybotsStunnedFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitStunnedexpired_Implementation(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddTag<FFloppybotsStunnedexpiredFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::RemoveStunnedexpired_Implementation(int32 Entity, FFloppybotsStunnedexpired Stunnedexpired) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveTag<FFloppybotsStunnedexpiredFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitPushcharge_Implementation(int32 Entity, FFloppybotsPushcharge Pushcharge) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FFloppybotsPushchargeFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FFloppybotsPushchargeFragment{ Pushcharge });
	}
}
void UFloppybotsMassSpawner::UpdatePushcharge_Implementation(int32 Entity, FFloppybotsPushcharge Pushcharge) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Pushcharge](FMassEntityManager& entity_manager) {
			auto fragment = entity_manager.GetFragmentDataPtr<FFloppybotsPushchargeFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FFloppybotsPushchargeFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Pushcharge;
		});
	}
}
void UFloppybotsMassSpawner::RemovePushcharge_Implementation(int32 Entity, FFloppybotsPushcharge Pushcharge) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FFloppybotsPushchargeFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitEnemy_Implementation(int32 Entity, FFloppybotsEnemy Enemy) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FFloppybotsEnemyFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FFloppybotsEnemyFragment{ Enemy });
	}
}
void UFloppybotsMassSpawner::UpdateEnemy_Implementation(int32 Entity, FFloppybotsEnemy Enemy) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Enemy](FMassEntityManager& entity_manager) {
			auto fragment = entity_manager.GetFragmentDataPtr<FFloppybotsEnemyFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FFloppybotsEnemyFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Enemy;
		});
	}
}
void UFloppybotsMassSpawner::RemoveEnemy_Implementation(int32 Entity, FFloppybotsEnemy Enemy) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FFloppybotsEnemyFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitVelocity_Implementation(int32 Entity, FFloppybotsVelocity Velocity) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FFloppybotsVelocityFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FFloppybotsVelocityFragment{ Velocity });
	}
}
void UFloppybotsMassSpawner::UpdateVelocity_Implementation(int32 Entity, FFloppybotsVelocity Velocity) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Velocity](FMassEntityManager& entity_manager) {
			auto fragment = entity_manager.GetFragmentDataPtr<FFloppybotsVelocityFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FFloppybotsVelocityFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Velocity;
		});
	}
}
void UFloppybotsMassSpawner::RemoveVelocity_Implementation(int32 Entity, FFloppybotsVelocity Velocity) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FFloppybotsVelocityFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitPushing_Implementation(int32 Entity, FFloppybotsPushing Pushing) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FFloppybotsPushingFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FFloppybotsPushingFragment{ Pushing });
	}
}
void UFloppybotsMassSpawner::UpdatePushing_Implementation(int32 Entity, FFloppybotsPushing Pushing) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Pushing](FMassEntityManager& entity_manager) {
			auto fragment = entity_manager.GetFragmentDataPtr<FFloppybotsPushingFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FFloppybotsPushingFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Pushing;
		});
	}
}
void UFloppybotsMassSpawner::RemovePushing_Implementation(int32 Entity, FFloppybotsPushing Pushing) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FFloppybotsPushingFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitToggle_Implementation(int32 Entity, FFloppybotsToggle Toggle) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FFloppybotsToggleFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FFloppybotsToggleFragment{ Toggle });
	}
}
void UFloppybotsMassSpawner::UpdateToggle_Implementation(int32 Entity, FFloppybotsToggle Toggle) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Toggle](FMassEntityManager& entity_manager) {
			auto fragment = entity_manager.GetFragmentDataPtr<FFloppybotsToggleFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FFloppybotsToggleFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Toggle;
		});
	}
}
void UFloppybotsMassSpawner::RemoveToggle_Implementation(int32 Entity, FFloppybotsToggle Toggle) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FFloppybotsToggleFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitMovedirection_Implementation(int32 Entity, FFloppybotsMovedirection Movedirection) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FFloppybotsMovedirectionFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FFloppybotsMovedirectionFragment{ Movedirection });
	}
}
void UFloppybotsMassSpawner::UpdateMovedirection_Implementation(int32 Entity, FFloppybotsMovedirection Movedirection) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Movedirection](FMassEntityManager& entity_manager) {
			auto fragment = entity_manager.GetFragmentDataPtr<FFloppybotsMovedirectionFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FFloppybotsMovedirectionFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Movedirection;
		});
	}
}
void UFloppybotsMassSpawner::RemoveMovedirection_Implementation(int32 Entity, FFloppybotsMovedirection Movedirection) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FFloppybotsMovedirectionFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::InitRemovepushingtag_Implementation(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddTag<FFloppybotsRemovepushingtagFragment>(entity_handle);
	}
}
void UFloppybotsMassSpawner::RemoveRemovepushingtag_Implementation(int32 Entity, FFloppybotsRemovepushingtag Removepushingtag) {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveTag<FFloppybotsRemovepushingtagFragment>(entity_handle);
	}
}
auto UFloppybotsMassSpawner::GetEcsactMassEntityHandles(int32 Entity) -> TArray<FMassEntityHandle> {
	UE_LOG(LogTemp, Error, TEXT("GetEcsactMassEntityHandless must be implemented for EcsactMassEntitySpawner"));
	return TArray<FMassEntityHandle>{};
}
auto UOneToOneFloppybotsMassSpawner::EntityCreated_Implementation(int32 Entity) -> void {
	auto* world = GetWorld();
	check(world);

	auto* config = GetEntityMassConfig();
	if(!config) {
		UE_LOG(Ecsact, Warning, TEXT("%s GetEntityMassConfig() returned null"), *GetClass()->GetName());
		return;
	}
	const auto& entity_template = config->GetOrCreateEntityTemplate(*world);
	auto new_entity_handles = TArray<FMassEntityHandle>{};

	auto mass_spawner = world->GetSubsystem<UMassSpawnerSubsystem>();
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	mass_spawner->SpawnEntities(entity_template, 1, new_entity_handles);
	MassEntities.Add(static_cast<ecsact_entity_id>(Entity), new_entity_handles);
	for(auto entity_handle : new_entity_handles) {
		entity_manager.Defer().AddFragment<FEcsactEntityFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FEcsactEntityFragment{ static_cast<ecsact_entity_id>(Entity) });
		;
	}
}
auto UOneToOneFloppybotsMassSpawner::EntityDestroyed_Implementation(int32 Entity) -> void {
	auto* world = GetWorld();
	check(world);

	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	auto old_entity_handles = TArray<FMassEntityHandle>{};
	MassEntities.RemoveAndCopyValue(static_cast<ecsact_entity_id>(Entity), old_entity_handles);
	for(auto entity_handle : old_entity_handles) {
		entity_manager.Defer().DestroyEntity(entity_handle);
	}
}
auto UOneToOneFloppybotsMassSpawner::GetEcsactMassEntityHandles(int32 Entity) -> TArray<FMassEntityHandle> {
	auto handles = MassEntities.Find(static_cast<ecsact_entity_id>(Entity));
	if(!handles)
		return {};
	return *handles;
}
auto UOneToOneFloppybotsMassSpawner::GetEntityMassConfig() const -> UMassEntityConfigAsset* {
	return MassEntityConfigAsset;
}