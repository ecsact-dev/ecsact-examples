#include "EcsactBenchmark__ecsact__mass__ue.h"
#include "Engine/World.h"
#include "MassEntitySubsystem.h"
#include "MassSpawnerSubsystem.h"
#include "MassCommandBuffer.h"

void UBenchmarkMassSpawner::InitCounter_Implementation(int32 Entity, FBenchmarkCounter Counter)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddFragment<FBenchmarkCounterFragment>(entity_handle);
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(entity_handle, FBenchmarkCounterFragment{Counter});
		
	}
}
void UBenchmarkMassSpawner::UpdateCounter_Implementation(int32 Entity, FBenchmarkCounter Counter)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>([this, Entity, entity_handle, Counter](FMassEntityManager& entity_manager)
		 {
			auto fragment = entity_manager.GetFragmentDataPtr<FBenchmarkCounterFragment>(entity_handle);
			if(!fragment) {
				UE_LOG(Ecsact, Warning, TEXT("%s fragment FBenchmarkCounterFragment does not exist for entity %i"), *GetClass()->GetName(), Entity);
				return;
			}
			fragment->component = Counter;
			
		});
		
	}
}
void UBenchmarkMassSpawner::RemoveCounter_Implementation(int32 Entity, FBenchmarkCounter Counter)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveFragment<FBenchmarkCounterFragment>(entity_handle);
		
	}
}
void UBenchmarkMassSpawner::InitMassonly_Implementation(int32 Entity, FBenchmarkMassonly Massonly)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddTag<FBenchmarkMassonlyFragment>(entity_handle);
		
	}
}
void UBenchmarkMassSpawner::RemoveMassonly_Implementation(int32 Entity, FBenchmarkMassonly Massonly)
 {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveTag<FBenchmarkMassonlyFragment>(entity_handle);
		
	}
}
auto UBenchmarkMassSpawner::GetEcsactMassEntityHandles(int32 Entity) -> TArray<FMassEntityHandle> {
	UE_LOG(LogTemp, Error, TEXT("GetEcsactMassEntityHandless must be implemented for EcsactMassEntitySpawner"));
	return TArray<FMassEntityHandle>{};
	
}
auto UOneToOneBenchmarkMassSpawner::EntityCreated_Implementation(int32 Entity) -> void {
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
}auto UOneToOneBenchmarkMassSpawner::EntityDestroyed_Implementation(int32 Entity) -> void {
	auto* world = GetWorld();
	check(world);
	
	auto& entity_manager = world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	
	auto old_entity_handles = TArray<FMassEntityHandle>{};
	MassEntities.RemoveAndCopyValue(static_cast<ecsact_entity_id>(Entity),old_entity_handles);
	for(auto entity_handle : old_entity_handles) {
		entity_manager.Defer().DestroyEntity(entity_handle);
		
	}
}
auto UOneToOneBenchmarkMassSpawner::GetEcsactMassEntityHandles(int32 Entity) -> TArray<FMassEntityHandle> {
	auto handles = MassEntities.Find(static_cast<ecsact_entity_id>(Entity));
	if(!handles) return {};
	return *handles;
	
}
auto UOneToOneBenchmarkMassSpawner::GetEntityMassConfig() const -> UMassEntityConfigAsset*
 {
	return MassEntityConfigAsset;
	
}