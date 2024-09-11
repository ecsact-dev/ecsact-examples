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

UEntitySpawner::UEntitySpawner() {
	// In this example we're assuming the entities are spawned on the first world
	// that is initialized. In a real application you may have a specific world
	// you want entities to be spawned.
	FWorldDelegates::OnPreWorldInitialization.AddUObject(
		this,
		&ThisClass::OnPreWorldInitialization
	);
	FWorldDelegates::OnPostWorldCleanup.AddUObject(
		this,
		&ThisClass::OnPostWorldCleanup
	);
}

auto UEntitySpawner::OnPreWorldInitialization( //
	UWorld*                            World,
	const UWorld::InitializationValues IV
) -> void {
	if(EntitySpawnerWorld == nullptr) {
		EntitySpawnerWorld = World;
	}
}

auto UEntitySpawner::OnPostWorldCleanup( //
	UWorld* World,
	bool    bSessionEnded,
	bool    bCleanupResources
) -> void {
	if(EntitySpawnerWorld == World) {
		EntitySpawnerWorld = nullptr;
	}
}

auto UEntitySpawner::GetWorld() const -> UWorld* {
	check(EntitySpawnerWorld != nullptr);
	return EntitySpawnerWorld;
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
	auto actor = GetWorld()->SpawnActor(EntityActorClass.Get(), &spawn_pos);
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
