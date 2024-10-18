#include "EcsactActorSyncSubsystem.h"
#include "EcsactActor.h"

auto UEcsactActorSyncSubsystem::RunnerStart_Implementation( //
	class UEcsactRunner* Runner
) -> void {
}

auto UEcsactActorSyncSubsystem::UpdatePosition_Implementation( //
	int32               Entity,
	FExampleFpsPosition Position
) -> void {
	auto ecsact_actor_weak_ptr =
		EntityActors.Find(static_cast<ecsact_entity_id>(Entity));
	if(!ecsact_actor_weak_ptr || !ecsact_actor_weak_ptr->IsValid()) {
		return;
	}

	auto ecsact_actor = ecsact_actor_weak_ptr->Get();
	ecsact_actor->SetWorldLocation(FVector{
		Position.X,
		Position.Y,
		Position.Z,
	});
}

auto UEcsactActorSyncSubsystem::RegisterEcsactActor( //
	ecsact_entity_id                   Entity,
	TWeakObjectPtr<class UEcsactActor> EcsactActor
) -> void {
	EntityActors.Add(Entity, EcsactActor);
}

auto UEcsactActorSyncSubsystem::DeregisterEcsactActor( //
	ecsact_entity_id                   Entity,
	TWeakObjectPtr<class UEcsactActor> EcsactActor
) -> void {
	auto existing = EntityActors.Find(Entity);
	if(existing && *existing == EcsactActor) {
		EntityActors.Remove(Entity);
	}
}
