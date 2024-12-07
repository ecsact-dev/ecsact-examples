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
			.AddComponent(example::fps::Toggle{.streaming = true})
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
	FExampleFpsMassentity MEntityTag
) -> void {
	UE_LOG(LogTemp, Warning, TEXT("Mass Entity found, adding to Mass Spawner"));

	auto  EcsactEntity = static_cast<ecsact_entity_id>(Entity);
	auto& EntityPool = EntityPools.FindOrAdd(EcsactEntity);

	using std::get;

	const auto& Position = get<std::optional<FExampleFpsPosition>>(EntityPool);
	auto& TMassEntity = get<std::optional<FExampleFpsMassentity>>(EntityPool);

	TMassEntity = MEntityTag;
	if(Position == std::nullopt) {
		return;
	}
	Spawn(EcsactEntity, *Position);
}

auto UEcsactEntityMassSpawner::InitPosition_Implementation(
	int32               Entity,
	FExampleFpsPosition Position
) -> void {
	auto  EcsactEntity = static_cast<ecsact_entity_id>(Entity);
	auto& EntityPool = EntityPools.FindOrAdd(EcsactEntity);

	using std::get;

	const auto& TMassEntity =
		get<std::optional<FExampleFpsMassentity>>(EntityPool);
	auto& TPosition = get<std::optional<FExampleFpsPosition>>(EntityPool);

	TPosition = Position;
	if(TMassEntity == std::nullopt) {
		return;
	}
	Spawn(EcsactEntity, Position);
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
			check(EntityHandle.IsValid());
			check(EntityHandle.IsSet());
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("Ecsact Position updated to %f, %f, %f"),
				Position.X,
				Position.Y,
				Position.Z
			);
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

		if(EntityManager.IsProcessing()) {
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
		} else {
			EntityManager.Defer().PushCommand<FMassDeferredAddCommand>(
				[EntityHandle, Entity, ShouldStream = StreamEntities, vec](
					auto& EntityManager
				) {
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
						[ShouldStream](void* fragment, const UScriptStruct& FragmentType) {
							auto* StreamFragment =
								static_cast<FEcsactStreamFragment*>(fragment);
							StreamFragment->SetStream(ShouldStream);
						}
					);
				}
			);
		}
	}
	EntityManager.FlushCommands();
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

	UWorld* world = GetWorld();
	auto    MassEntitySubsystem = world->GetSubsystem<UMassEntitySubsystem>();

	FMassEntityManager& EntityManager =
		MassEntitySubsystem->GetMutableEntityManager();

	auto EcsactEntity = static_cast<ecsact_entity_id>(Entity);

	if(!MassEntities.Contains(EcsactEntity)) {
		UE_LOG(LogTemp, Error, TEXT("Unknown Entity not found (Mass Spawner)"));
		return;
	}

	auto EntityHandles = *MassEntities.Find(EcsactEntity);

	for(auto EntityHandle : EntityHandles) {
		if(EntityManager.IsProcessing()) {
			EntityManager.Defer().PushCommand<FMassDeferredSetCommand>(
				[EntityHandle, Streaming = Toggle.Streaming](auto& EntityManager) {
					auto* StreamFragment =
						EntityManager.template GetFragmentDataPtr<FEcsactStreamFragment>(
							EntityHandle
						);
					StreamFragment->SetStream(static_cast<bool>(Streaming));
				}
			);
		} else {
			auto* StreamFragent =
				EntityManager.GetFragmentDataPtr<FEcsactStreamFragment>(EntityHandle);
			StreamFragent->SetStream(static_cast<bool>(Toggle.Streaming));
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
