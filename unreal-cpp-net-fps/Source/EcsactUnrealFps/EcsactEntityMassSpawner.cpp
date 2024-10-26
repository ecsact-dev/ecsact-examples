#include "EcsactEntityMassSpawner.h"

#include "EcsactUnrealFps/EcsactUnrealFps.ecsact.hh"
#include "MassEntityTemplate.h"
#include "MassSpawnerSubsystem.h"
#include "MassEntitySubsystem.h"
#include "MassEntityTemplateRegistry.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "Fragments/EcsactFragments.h"

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
			.AddComponent(example::fps::MassEntity{})
			.OnCreate(TDelegate<void(ecsact_entity_id)>::CreateLambda( //
				[](auto entity) {
					UE_LOG(
						LogTemp,
						Warning,
						TEXT("Created mass entity %i"),
						static_cast<int>(entity)
					);
				}
			));
	}
}

auto UEcsactEntityMassSpawner::InitMassentity_Implementation(
	int32                 Entity,
	FExampleFpsMassentity massEntity
) -> void {
	UE_LOG(LogTemp, Warning, TEXT("Mass Entity found, adding to Mass Spawner"));

	UWorld* world = GetWorld();

	const FMassEntityTemplate& EntityTemplate =
		MassEntityConfigAsset->GetOrCreateEntityTemplate(*world);

	FMassEntityTemplate EntityTemplateCopy = EntityTemplate;

	auto MassSpawner = world->GetSubsystem<UMassSpawnerSubsystem>();
	auto MassEntity = world->GetSubsystem<UMassEntitySubsystem>();

	FMassEntityManager& EntityManager = MassEntity->GetMutableEntityManager();

	MassSpawner->SpawnEntities(EntityTemplate, 1, EntityHandles);
	for(auto& EntityHandle : EntityHandles) {
		EntityManager.AddFragmentToEntity(
			EntityHandle,
			FEcsactEntityFragment::StaticStruct(),
			[Entity](void* fragment, const UScriptStruct& FragmentType) {
				FEcsactEntityFragment* EntityFragment =
					static_cast<FEcsactEntityFragment*>(fragment);
				EntityFragment->SetId(static_cast<ecsact_entity_id>(Entity));
			}
		);
	}
}
