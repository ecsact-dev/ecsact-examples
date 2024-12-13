#include "EcsactEntityMassSpawner.h"

#include "MassCommands.h"
#include "MassMovementFragments.h"
#include "MassStateTreeSubsystem.h"
#include "Math/Vector.h"
#include "EcsactUnrealFps/EcsactUnrealFps.ecsact.hh"
#include "EcsactUnrealFps/EcsactUnrealFps__ecsact__ue.h"
#include "MassEntityTemplate.h"
#include "MassSpawnerSubsystem.h"
#include "MassEntitySubsystem.h"
#include "MassEntityTemplateRegistry.h"
#include "MassEntityManager.h"
#include "MassCommonFragments.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "Fragments/EcsactFragments.h"
#include "EcsactUnrealFps.ecsact.hh"
#include "EcsactUnrealFps/Commands/UpdateCommands.h"

auto UEcsactEntityMassSpawner::CreateMassEntities(int count) -> void {
	auto runner = GetRunner();
	check(runner);

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("CreateMassEntities, creating %i entities"),
		count
	);

	for(int i = 0; i < count; i++) {
		auto RandomPointX = FMath::RandRange(-2000, 2000);
		auto RandomPointY = FMath::RandRange(-2000, 2000);

		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Setting random position to %i %i"),
			RandomPointX,
			RandomPointY
		);

		runner->CreateEntity()
			.AddComponent(example::fps::Position{
				.x = static_cast<float>(RandomPointX),
				.y = static_cast<float>(RandomPointY),
				.z = 0
			})
			.AddComponent(example::fps::Enemy{})
			.AddComponent(example::fps::Velocity{})
			.AddComponent(example::fps::Toggle{.streaming = StreamEntities})
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

auto UEcsactEntityMassSpawner::EntityCreated_Implementation( //
	int32 Entity
) -> void {
	checkSlow(!MassEntities.Contains(static_cast<ecsact_entity_id>(Entity)));

	auto* world = GetWorld();

	const FMassEntityTemplate& entity_template =
		MassEntityConfigAsset->GetOrCreateEntityTemplate(*world);
	auto new_entity_handles = TArray<FMassEntityHandle>{};

	auto  mass_spawner = world->GetSubsystem<UMassSpawnerSubsystem>();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	mass_spawner->SpawnEntities(entity_template, 1, new_entity_handles);
	for(auto entity_handle : new_entity_handles) {
		entity_manager.AddFragmentToEntity(
			entity_handle,
			FEcsactEntityFragment::StaticStruct(),
			[Entity](void* fragment, const UScriptStruct&) {
				static_cast<FEcsactEntityFragment*>(fragment)->SetId(
					static_cast<ecsact_entity_id>(Entity)
				);
			}
		);
	}

	MassEntities.Add(static_cast<ecsact_entity_id>(Entity), new_entity_handles);
}

auto UEcsactEntityMassSpawner::EntityDestroyed_Implementation( //
	int32 Entity
) -> void {
	checkSlow(MassEntities.Contains(static_cast<ecsact_entity_id>(Entity)));

	auto* world = GetWorld();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	auto old_entity_handles = TArray<FMassEntityHandle>{};
	MassEntities.RemoveAndCopyValue(
		static_cast<ecsact_entity_id>(Entity),
		old_entity_handles
	);

	for(auto entity_handle : old_entity_handles) {
		entity_manager.Defer().DestroyEntity(entity_handle);
	}
}

auto UEcsactEntityMassSpawner::InitEnemy_Implementation(
	int32            Entity,
	FExampleFpsEnemy Enemy
) -> void {
}

auto UEcsactEntityMassSpawner::InitPosition_Implementation(
	int32               Entity,
	FExampleFpsPosition Position
) -> void {
	checkSlow(MassEntities.Contains(static_cast<ecsact_entity_id>(Entity)));

	auto* world = GetWorld();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	auto entity_handles =
		MassEntities.FindChecked(static_cast<ecsact_entity_id>(Entity));
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(
			entity_handle,
			FEcsactPositionFragment()
		);
	}
}

auto UEcsactEntityMassSpawner::UpdatePosition_Implementation(
	int32               Entity,
	FExampleFpsPosition Position
) -> void {
	checkSlow(MassEntities.Contains(static_cast<ecsact_entity_id>(Entity)));

	auto* world = GetWorld();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	const auto& entity_handles =
		MassEntities.FindChecked(static_cast<ecsact_entity_id>(Entity));
	for(auto entity_handle : entity_handles) {
		entity_manager.GetFragmentDataPtr<FEcsactPositionFragment>(entity_handle)
			->SetPosition(FVector{
				Position.X,
				Position.Y,
				Position.Z,
			});
	}
}

auto UEcsactEntityMassSpawner::InitToggle_Implementation( //
	int32             Entity,
	FExampleFpsToggle Toggle
) -> void {
	UpdateToggle_Implementation(Entity, Toggle);
}

auto UEcsactEntityMassSpawner::UpdateToggle_Implementation( //
	int32             Entity,
	FExampleFpsToggle Toggle
) -> void {
	checkSlow(MassEntities.Contains(static_cast<ecsact_entity_id>(Entity)));

	if(!StreamEntities) {
		return;
	}

	auto* world = GetWorld();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	auto entity_handles =
		MassEntities.FindChecked(static_cast<ecsact_entity_id>(Entity));

	for(auto Entity : entity_handles) {
		if(Toggle.Streaming) {
			entity_manager.Defer().AddTag<FEcsactStreamTag>(Entity);
		} else {
			entity_manager.Defer().RemoveTag<FEcsactStreamTag>(Entity);
		}
	}
}

auto UEcsactEntityMassSpawner::Push(int32 PlayerId) -> void {
	auto runner = GetRunner();
	check(runner);

	auto PushAction = example::fps::Push{
		.player_id = PlayerId,
		.radius = 500,
		.tick_count = 200,
		.force = 2,
	};
	runner->PushAction(PushAction);
}
