#include "EcsactEntityMassSpawner.h"

#include "EcsactUnrealFps/EcsactUnrealFps.ecsact.hh"
#include "MassSpawnerSubsystem.h"
#include "MassEntityTemplateRegistry.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "InstancedStruct.h"
#include ""

auto UEcsactEntityMassSpawner::CreateMassEntities(int count) -> void {
	auto runner = EcsactUnrealExecution::Runner();
	check(runner.IsValid());

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("CreateMassEntities, creating {} entities"),
		count
	);

	for(int i = 0; i < count; i++) {
		runner->CreateEntity()
			.AddComponent(example::fps::Position{})
			.AddComponent(example::fps::MassEntity{});
	}
}

auto UEcsactEntityMassSpawner::InitMassentity_Implementation(
	int32                 Entity,
	FExampleFpsMassentity massEntity
) -> void {
	UE_LOG(LogTemp, Warning, TEXT("Mass Entity found, adding to Mass Spawner"));

	UWorld* world = GetWorld();

	auto& EntityTemplate =
		MassEntityConfigAsset->GetOrCreateEntityTemplate(*world);
	auto MassSpawner = world->GetSubsystem<UMassSpawnerSubsystem>();

	MassSpawner->SpawnEntities(EntityTemplate, 1, EntityHandles);
}
