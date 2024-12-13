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

auto UEcsactEntityMassSpawner::CheckMassEntities(
	int32        Entity,
	const TCHAR* EventName
) -> bool {
	// TODO: We really shouldn't need to do this test, but in some cases create
	// entity event doesn't happen
	auto has_entity_handles =
		MassEntities.Contains(static_cast<ecsact_entity_id>(Entity));
	if(!has_entity_handles) {
		UE_LOG(
			LogTemp,
			Error,
			TEXT("EntityCreated event did not happen for entity %i - Ignoring %s"),
			Entity,
			EventName
		);
	}
	return has_entity_handles;
}

auto UEcsactEntityMassSpawner::EntityCreated_Implementation( //
	int32 Entity
) -> void {
	checkSlow(!MassEntities.Contains(static_cast<ecsact_entity_id>(Entity)));

	auto* world = GetWorld();

	const auto& entity_template =
		MassEntityConfigAsset->GetOrCreateEntityTemplate(*world);
	auto new_entity_handles = TArray<FMassEntityHandle>{};

	auto  mass_spawner = world->GetSubsystem<UMassSpawnerSubsystem>();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	mass_spawner->SpawnEntities(entity_template, 1, new_entity_handles);
	for(auto entity_handle : new_entity_handles) {
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(
			entity_handle,
			FEcsactEntityFragment{static_cast<ecsact_entity_id>(Entity)}
		);
	}

	MassEntities.Add(static_cast<ecsact_entity_id>(Entity), new_entity_handles);
}

auto UEcsactEntityMassSpawner::EntityDestroyed_Implementation( //
	int32 Entity
) -> void {
	if(!CheckMassEntities(Entity, TEXT("EntityDestroyed"))) {
		return;
	}

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
	if(!CheckMassEntities(Entity, TEXT("InitEnemy"))) {
		return;
	}
}

auto UEcsactEntityMassSpawner::InitPosition_Implementation(
	int32               Entity,
	FExampleFpsPosition Position
) -> void {
	if(!CheckMassEntities(Entity, TEXT("InitPosition"))) {
		return;
	}

	auto* world = GetWorld();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	auto entity_handles =
		MassEntities.FindChecked(static_cast<ecsact_entity_id>(Entity));
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(
			entity_handle,
			FEcsactPositionFragment{FVector{
				Position.X,
				Position.Y,
				Position.Z,
			}}
		);
	}
}

auto UEcsactEntityMassSpawner::UpdatePosition_Implementation(
	int32               Entity,
	FExampleFpsPosition Position
) -> void {
	if(!CheckMassEntities(Entity, TEXT("UpdatePosition"))) {
		return;
	}

	auto* world = GetWorld();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	const auto& entity_handles =
		MassEntities.FindChecked(static_cast<ecsact_entity_id>(Entity));
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>(
			[entity_handle, Position](FMassEntityManager& entity_manager) {
				entity_manager
					.GetFragmentDataPtr<FEcsactPositionFragment>(entity_handle)
					->SetPosition(FVector{
						Position.X,
						Position.Y,
						Position.Z,
					});
			}
		);
	}
}

auto UEcsactEntityMassSpawner::InitToggle_Implementation( //
	int32             Entity,
	FExampleFpsToggle Toggle
) -> void {
	if(!CheckMassEntities(Entity, TEXT("InitToggle"))) {
		return;
	}
	UpdateToggle_Implementation(Entity, Toggle);
}

auto UEcsactEntityMassSpawner::UpdateToggle_Implementation( //
	int32             Entity,
	FExampleFpsToggle Toggle
) -> void {
	if(!CheckMassEntities(Entity, TEXT("UpdateToggle"))) {
		return;
	}

	if(!StreamEntities) {
		return;
	}

	auto* world = GetWorld();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	auto entity_handles =
		MassEntities.FindChecked(static_cast<ecsact_entity_id>(Entity));

	for(auto entity_handle : entity_handles) {
		if(Toggle.Streaming) {
			entity_manager.Defer().AddTag<FEcsactStreamTag>(entity_handle);
		} else {
			entity_manager.Defer().RemoveTag<FEcsactStreamTag>(entity_handle);
		}
	}
}

auto UEcsactEntityMassSpawner::Push(int32 PlayerId) -> void {
	auto runner = GetRunner();
	check(runner);

	auto PushAction = example::fps::Push{
		.player_id = PlayerId,
		.radius = 500,
		.tick_count = 20,
		.force = 50,
	};
	runner->PushAction(PushAction);
}
