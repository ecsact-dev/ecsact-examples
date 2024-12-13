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
			.AddComponent(example::fps::MassEntity{})
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
	int32                 Entity,
	FExampleFpsMassentity MEntityTag
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
	entity_manager.Defer().PushCommand<FMassDeferredAddCommand>(
		[entity_handles](FMassEntityManager& entity_manager) {
			for(auto entity_handle : entity_handles) {
				// entity_manager.AddFragmentToEntity
			}
		}
	);
}

auto UEcsactEntityMassSpawner::UpdatePosition_Implementation(
	int32               Entity,
	FExampleFpsPosition Position
) -> void {
	auto EcsactEntity = static_cast<ecsact_entity_id>(Entity);
	if(MassEntities.Contains(EcsactEntity)) {
		auto EntityHandles =
			*MassEntities.Find(static_cast<ecsact_entity_id>(Entity));

		UWorld* world = GetWorld();

		auto MassEntity = world->GetSubsystem<UMassEntitySubsystem>();
		FMassEntityManager& EntityManager = MassEntity->GetMutableEntityManager();

		auto vec = FVector{Position.X, Position.Y, Position.Z};

		for(auto EntityHandle : EntityHandles) {
			if(EntityManager.IsProcessing()) {
				EntityManager.Defer().PushCommand<FMassDeferredSetCommand>(
					[EntityHandle, vec](auto& EntityManager) {
						auto* PositionFragment =
							EntityManager
								.template GetFragmentDataPtr<FEcsactPositionFragment>(
									EntityHandle
								);
						PositionFragment->SetPosition(vec);
					}
				);
			} else {
				auto* PositionFragment =
					EntityManager.GetFragmentDataPtr<FEcsactPositionFragment>(EntityHandle
					);
				PositionFragment->SetPosition(vec);
			}
		}
		EntityManager.FlushCommands();
	}
}

auto UEcsactEntityMassSpawner::Spawn(
	ecsact_entity_id           Entity,
	const FExampleFpsPosition& Position
) -> void {
	UWorld* world = GetWorld();

	const FMassEntityTemplate& EntityTemplate =
		MassEntityConfigAsset->GetOrCreateEntityTemplate(*world);

	auto MassSpawner = world->GetSubsystem<UMassSpawnerSubsystem>();
	auto MassEntity = world->GetSubsystem<UMassEntitySubsystem>();

	FMassEntityManager& EntityManager = MassEntity->GetMutableEntityManager();
	auto&               DefaultBuffer = EntityManager.Defer();

	TArray<FMassEntityHandle> NewEntityHandles;

	MassSpawner->SpawnEntities(EntityTemplate, 1, NewEntityHandles);
	for(auto& EntityHandle : NewEntityHandles) {
		check(EntityHandle.IsValid());
		check(EntityHandle.IsSet());
		auto vec = FVector{Position.X, Position.Y, Position.Z};

		auto* TransformFragment =
			EntityManager.GetFragmentDataPtr<FTransformFragment>(EntityHandle);

		auto Transform = FTransform(vec);
		TransformFragment->SetTransform(Transform);

		DefaultBuffer.PushCommand<FTransformUpdateCommand>(
			EntityHandle,
			std::move(Transform)
		);

		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Entity Manager spawning entity at %f %f"),
			Position.X,
			Position.Y
		);

		EntityManager.AddFragmentToEntity(
			EntityHandle,
			FEcsactEntityFragment::StaticStruct(),
			[Entity](void* fragment, const UScriptStruct& FragmentType) {
				FEcsactEntityFragment* EntityFragment =
					static_cast<FEcsactEntityFragment*>(fragment);
				EntityFragment->SetId(static_cast<ecsact_entity_id>(Entity));
			}
		);

		EntityManager.AddFragmentToEntity(
			EntityHandle,
			FEcsactPositionFragment::StaticStruct(),
			[&vec](void* fragment, const UScriptStruct& FragmentType) {
				auto* PositionFragment =
					static_cast<FEcsactPositionFragment*>(fragment);
				PositionFragment->SetPosition(vec);
			}
		);

		EntityManager.AddFragmentToEntity(
			EntityHandle,
			FEcsactStreamFragment::StaticStruct(),
			[this](void* fragment, const UScriptStruct& FragmentType) {
				auto* StreamFragment = static_cast<FEcsactStreamFragment*>(fragment);
				StreamFragment->SetStream(StreamEntities);
			}
		);
	}

	MassEntities.Add(Entity, NewEntityHandles);
	EntityPools.Remove(Entity);
}

auto UEcsactEntityMassSpawner::UpdateToggle_Implementation( //
	int32             Entity,
	FExampleFpsToggle Toggle
) -> void {
	if(!StreamEntities) {
		return;
	}

	auto* world = GetWorld();
	auto  MassEntitySubsystem = world->GetSubsystem<UMassEntitySubsystem>();

	auto& EntityManager = MassEntitySubsystem->GetMutableEntityManager();

	auto EcsactEntity = static_cast<ecsact_entity_id>(Entity);
	auto EntityHandles = MassEntities.Find(EcsactEntity);
	if(!EntityHandles) {
		UE_LOG(LogTemp, Error, TEXT("Unknown Entity not found (Mass Spawner)"));
		return;
	}

	for(auto Entity : *EntityHandles) {
		if(Toggle.Streaming) {
			EntityManager.Defer().AddTag<FEcsactStreamTag>(Entity);
		} else {
			EntityManager.Defer().RemoveTag<FEcsactStreamTag>(Entity);
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
