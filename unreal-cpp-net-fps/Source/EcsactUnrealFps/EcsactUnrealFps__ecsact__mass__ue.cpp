#include "EcsactUnrealFps__ecsact__mass__ue.h"
#include "Engine/World.h"
#include "MassEntitySubsystem.h"
#include "MassSpawnerSubsystem.h"
#include "MassCommandBuffer.h"

void UExampleFpsMassSpawner::InitPlayer_Implementation(int32 Entity, FExampleFpsPlayer Player)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FExampleFpsPlayerFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FExampleFpsPlayerFragment{Player});
		
	}
}
void UExampleFpsMassSpawner::UpdatePlayer_Implementation(int32 Entity, FExampleFpsPlayer Player)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Player](FMassEntityManager& entity_manager)
		 {
			auto fragment = entity_manager.GetFragmentDataPtr<FExampleFpsPlayerFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FExampleFpsPlayerFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Player;
			
		});
		
	}
}
void UExampleFpsMassSpawner::RemovePlayer_Implementation(int32 Entity, FExampleFpsPlayer Player)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FExampleFpsPlayerFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitPusher_Implementation(int32 Entity, FExampleFpsPusher Pusher)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FExampleFpsPusherFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FExampleFpsPusherFragment{Pusher});
		
	}
}
void UExampleFpsMassSpawner::UpdatePusher_Implementation(int32 Entity, FExampleFpsPusher Pusher)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Pusher](FMassEntityManager& entity_manager)
		 {
			auto fragment = entity_manager.GetFragmentDataPtr<FExampleFpsPusherFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FExampleFpsPusherFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Pusher;
			
		});
		
	}
}
void UExampleFpsMassSpawner::RemovePusher_Implementation(int32 Entity, FExampleFpsPusher Pusher)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FExampleFpsPusherFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitPusherexpired_Implementation(int32 Entity, FExampleFpsPusherexpired Pusherexpired)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddTag<FExampleFpsPusherexpiredFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::RemovePusherexpired_Implementation(int32 Entity, FExampleFpsPusherexpired Pusherexpired)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveTag<FExampleFpsPusherexpiredFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitRotation_Implementation(int32 Entity, FExampleFpsRotation Rotation)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FExampleFpsRotationFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FExampleFpsRotationFragment{Rotation});
		
	}
}
void UExampleFpsMassSpawner::UpdateRotation_Implementation(int32 Entity, FExampleFpsRotation Rotation)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Rotation](FMassEntityManager& entity_manager)
		 {
			auto fragment = entity_manager.GetFragmentDataPtr<FExampleFpsRotationFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FExampleFpsRotationFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Rotation;
			
		});
		
	}
}
void UExampleFpsMassSpawner::RemoveRotation_Implementation(int32 Entity, FExampleFpsRotation Rotation)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FExampleFpsRotationFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitPosition_Implementation(int32 Entity, FExampleFpsPosition Position)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FExampleFpsPositionFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FExampleFpsPositionFragment{Position});
		
	}
}
void UExampleFpsMassSpawner::UpdatePosition_Implementation(int32 Entity, FExampleFpsPosition Position)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Position](FMassEntityManager& entity_manager)
		 {
			auto fragment = entity_manager.GetFragmentDataPtr<FExampleFpsPositionFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FExampleFpsPositionFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Position;
			
		});
		
	}
}
void UExampleFpsMassSpawner::RemovePosition_Implementation(int32 Entity, FExampleFpsPosition Position)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FExampleFpsPositionFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitStunned_Implementation(int32 Entity, FExampleFpsStunned Stunned)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FExampleFpsStunnedFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FExampleFpsStunnedFragment{Stunned});
		
	}
}
void UExampleFpsMassSpawner::UpdateStunned_Implementation(int32 Entity, FExampleFpsStunned Stunned)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Stunned](FMassEntityManager& entity_manager)
		 {
			auto fragment = entity_manager.GetFragmentDataPtr<FExampleFpsStunnedFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FExampleFpsStunnedFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Stunned;
			
		});
		
	}
}
void UExampleFpsMassSpawner::RemoveStunned_Implementation(int32 Entity, FExampleFpsStunned Stunned)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FExampleFpsStunnedFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitStunnedexpired_Implementation(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddTag<FExampleFpsStunnedexpiredFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::RemoveStunnedexpired_Implementation(int32 Entity, FExampleFpsStunnedexpired Stunnedexpired)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveTag<FExampleFpsStunnedexpiredFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitPushcharge_Implementation(int32 Entity, FExampleFpsPushcharge Pushcharge)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FExampleFpsPushchargeFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FExampleFpsPushchargeFragment{Pushcharge});
		
	}
}
void UExampleFpsMassSpawner::UpdatePushcharge_Implementation(int32 Entity, FExampleFpsPushcharge Pushcharge)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Pushcharge](FMassEntityManager& entity_manager)
		 {
			auto fragment = entity_manager.GetFragmentDataPtr<FExampleFpsPushchargeFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FExampleFpsPushchargeFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Pushcharge;
			
		});
		
	}
}
void UExampleFpsMassSpawner::RemovePushcharge_Implementation(int32 Entity, FExampleFpsPushcharge Pushcharge)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FExampleFpsPushchargeFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitEnemy_Implementation(int32 Entity, FExampleFpsEnemy Enemy)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FExampleFpsEnemyFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FExampleFpsEnemyFragment{Enemy});
		
	}
}
void UExampleFpsMassSpawner::UpdateEnemy_Implementation(int32 Entity, FExampleFpsEnemy Enemy)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Enemy](FMassEntityManager& entity_manager)
		 {
			auto fragment = entity_manager.GetFragmentDataPtr<FExampleFpsEnemyFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FExampleFpsEnemyFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Enemy;
			
		});
		
	}
}
void UExampleFpsMassSpawner::RemoveEnemy_Implementation(int32 Entity, FExampleFpsEnemy Enemy)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FExampleFpsEnemyFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitVelocity_Implementation(int32 Entity, FExampleFpsVelocity Velocity)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FExampleFpsVelocityFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FExampleFpsVelocityFragment{Velocity});
		
	}
}
void UExampleFpsMassSpawner::UpdateVelocity_Implementation(int32 Entity, FExampleFpsVelocity Velocity)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Velocity](FMassEntityManager& entity_manager)
		 {
			auto fragment = entity_manager.GetFragmentDataPtr<FExampleFpsVelocityFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FExampleFpsVelocityFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Velocity;
			
		});
		
	}
}
void UExampleFpsMassSpawner::RemoveVelocity_Implementation(int32 Entity, FExampleFpsVelocity Velocity)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FExampleFpsVelocityFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitPushing_Implementation(int32 Entity, FExampleFpsPushing Pushing)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FExampleFpsPushingFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FExampleFpsPushingFragment{Pushing});
		
	}
}
void UExampleFpsMassSpawner::UpdatePushing_Implementation(int32 Entity, FExampleFpsPushing Pushing)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Pushing](FMassEntityManager& entity_manager)
		 {
			auto fragment = entity_manager.GetFragmentDataPtr<FExampleFpsPushingFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FExampleFpsPushingFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Pushing;
			
		});
		
	}
}
void UExampleFpsMassSpawner::RemovePushing_Implementation(int32 Entity, FExampleFpsPushing Pushing)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FExampleFpsPushingFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitToggle_Implementation(int32 Entity, FExampleFpsToggle Toggle)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FExampleFpsToggleFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FExampleFpsToggleFragment{Toggle});
		
	}
}
void UExampleFpsMassSpawner::UpdateToggle_Implementation(int32 Entity, FExampleFpsToggle Toggle)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Toggle](FMassEntityManager& entity_manager)
		 {
			auto fragment = entity_manager.GetFragmentDataPtr<FExampleFpsToggleFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FExampleFpsToggleFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Toggle;
			
		});
		
	}
}
void UExampleFpsMassSpawner::RemoveToggle_Implementation(int32 Entity, FExampleFpsToggle Toggle)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FExampleFpsToggleFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitMovedirection_Implementation(int32 Entity, FExampleFpsMovedirection Movedirection)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FExampleFpsMovedirectionFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FExampleFpsMovedirectionFragment{Movedirection});
		
	}
}
void UExampleFpsMassSpawner::UpdateMovedirection_Implementation(int32 Entity, FExampleFpsMovedirection Movedirection)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Movedirection](FMassEntityManager& entity_manager)
		 {
			auto fragment = entity_manager.GetFragmentDataPtr<FExampleFpsMovedirectionFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FExampleFpsMovedirectionFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Movedirection;
			
		});
		
	}
}
void UExampleFpsMassSpawner::RemoveMovedirection_Implementation(int32 Entity, FExampleFpsMovedirection Movedirection)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FExampleFpsMovedirectionFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::InitRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddTag<FExampleFpsRemovepushingtagFragment>(entity_handle);
		
	}
}
void UExampleFpsMassSpawner::RemoveRemovepushingtag_Implementation(int32 Entity, FExampleFpsRemovepushingtag Removepushingtag)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveTag<FExampleFpsRemovepushingtagFragment>(entity_handle);
		
	}
}
auto UExampleFpsMassSpawner::GetEcsactMassEntityHandles(int32 Entity) -> TArray<FMassEntityHandle> {
	UE_LOG(LogTemp, Error, TEXT("GetEcsactMassEntityHandless must be implemented for EcsactMassEntitySpawner"));
	return TArray<FMassEntityHandle>{};
	
}
auto UOneToOneExampleFpsMassSpawner::EntityCreated_Implementation(int32 Entity) -> void {
	auto* world = GetWorld();
	check(world);
	
	auto* config = GetEntityMassConfig();
	if(!config) {
		UE_LOG(Ecsact, Warning, TEXT("%s GetEntityMassConfig() returned null"), *GetClass()->GetName());
		return;
	}
	const auto& entity_template = config->GetOrCreateEntityTemplate(*world);
	auto new_entity_handles = TArray<FMassEntityHandle>{};
	
	auto  mass_spawner = world->GetSubsystem<UMassSpawnerSubsystem>();
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	
	mass_spawner->SpawnEntities(entity_template, 1, new_entity_handles);
	MassEntities.Add(static_cast<ecsact_entity_id>(Entity), new_entity_handles);
	for(auto entity_handle : new_entity_handles) {
		entity_manager.Defer().AddFragment<FEcsactEntityFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FEcsactEntityFragment{static_cast<ecsact_entity_id>(Entity)});
		;
		
	}
}auto UOneToOneExampleFpsMassSpawner::EntityDestroyed_Implementation(int32 Entity) -> void {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	
	auto old_entity_handles = TArray<FMassEntityHandle>{};
	MassEntities.RemoveAndCopyValue(static_cast<ecsact_entity_id>(Entity),old_entity_handles);
	for(auto entity_handle : old_entity_handles) {
		entity_manager.Defer().DestroyEntity(entity_handle);
		
	}
}
auto UOneToOneExampleFpsMassSpawner::GetEcsactMassEntityHandles(int32 Entity) -> TArray<FMassEntityHandle> {
	auto handles = MassEntities.Find(static_cast<ecsact_entity_id>(Entity));
	if(!handles) return {};
	return *handles;
	
}
auto UOneToOneExampleFpsMassSpawner::GetEntityMassConfig() const -> UMassEntityConfigAsset*
 {
	return MassEntityConfigAsset;
	
}