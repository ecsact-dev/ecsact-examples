#include "EntitySpawner.h"
#include "Engine/World.h"

auto UEntitySpawner::RunnerStart_Implementation(UEcsactRunner* Runner) -> void {
}

auto UEntitySpawner::RunnerStop_Implementation(UEcsactRunner* Runner) -> void {
	EntityActors.Empty();
}

auto UEntitySpawner::InitPosition_Implementation(
	int32            Entity,
	FExamplePosition Position
) -> void {
	auto spawn_pos = FVector{Position.X, Position.Y, Position.Z};
	auto actor = GWorld->SpawnActor(EntityActorClass.Get(), &spawn_pos);
	EntityActors.Add(Entity, actor);
}

auto UEntitySpawner::UpdatePosition_Implementation(
	int32            Entity,
	FExamplePosition Position
) -> void {
	auto actor = EntityActors.FindRef(Entity);
	if(actor) {
		actor->SetActorLocation(FVector(Position.X, Position.Y, Position.Z));
	}
}

auto UEntitySpawner::RemovePosition_Implementation(
	int32            Entity,
	FExamplePosition Position
) -> void {
	auto actor = EntityActors.FindRef(Entity);
	if(actor) {
		EntityActors.Remove(Entity);
	}
}
