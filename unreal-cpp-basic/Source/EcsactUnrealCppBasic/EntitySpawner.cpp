#include "EntitySpawner.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "Engine/World.h"

auto UEntitySpawner::CreateEntitySpawnPoint() -> void {
	EcsactUnrealExecution::Runner()
		->CreateEntity()
		.AddComponent(example::Position{})
		.AddComponent(example::Velocity{})
		.OnCreate(TDelegate<void(ecsact_entity_id)>::CreateLambda(
			[](ecsact_entity_id entity) {
				UE_LOG(LogTemp, Warning, TEXT("Initial entity created!"));
			}
		))
		.Finish();
}

auto UEntitySpawner::RunnerStart_Implementation(UEcsactRunner* Runner) -> void {
}

auto UEntitySpawner::RunnerStop_Implementation(UEcsactRunner* Runner) -> void {
	EntityActors.Empty();
}

auto UEntitySpawner::InitPosition_Implementation(
	int32            Entity,
	FExamplePosition Position
) -> void {
	UE_LOG(LogTemp, Warning, TEXT("Init Position!"));
	auto spawn_pos = FVector{Position.X, Position.Y, Position.Z};
	auto actor = GWorld->SpawnActor(EntityActorClass.Get(), &spawn_pos);
	EntityActors.Add(Entity, actor);
}

auto UEntitySpawner::UpdatePosition_Implementation(
	int32            Entity,
	FExamplePosition Position
) -> void {
	UE_LOG(LogTemp, Warning, TEXT("Update Position!"));
	auto actor = EntityActors.FindRef(Entity);
	if(actor) {
		actor->SetActorLocation(FVector(Position.X, Position.Y, Position.Z));
	}
}

auto UEntitySpawner::RemovePosition_Implementation(
	int32            Entity,
	FExamplePosition Position
) -> void {
	UE_LOG(LogTemp, Warning, TEXT("Remove Position!"));
	auto actor = EntityActors.FindRef(Entity);
	if(actor) {
		EntityActors.Remove(Entity);
	}
}
