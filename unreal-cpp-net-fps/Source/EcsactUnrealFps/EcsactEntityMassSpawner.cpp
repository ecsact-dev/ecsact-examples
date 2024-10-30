#include "EcsactEntityMassSpawner.h"

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
		auto RandomPointX = FMath::RandRange(0, 4000);
		auto RandomPointY = FMath::RandRange(0, 4000);

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

	auto& Position = get<std::optional<FExampleFpsPosition>>(EntityPool);
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

	auto& TMassEntity = get<std::optional<FExampleFpsMassentity>>(EntityPool);
	auto& TPosition = get<std::optional<FExampleFpsPosition>>(EntityPool);

	TPosition = Position;
	if(TMassEntity == std::nullopt) {
		return;
	}
	Spawn(EcsactEntity, Position);
}

auto UEcsactEntityMassSpawner::Spawn(
	ecsact_entity_id           Entity,
	const FExampleFpsPosition& Position
) -> void {
	UE_LOG(LogTemp, Warning, TEXT("In Spawn"));
	UWorld* world = GetWorld();

	const FMassEntityTemplate& EntityTemplate =
		MassEntityConfigAsset->GetOrCreateEntityTemplate(*world);

	auto MassSpawner = world->GetSubsystem<UMassSpawnerSubsystem>();
	auto MassEntity = world->GetSubsystem<UMassEntitySubsystem>();

	FMassEntityManager& EntityManager = MassEntity->GetMutableEntityManager();

	TArray<FMassEntityHandle> NewEntityHandles;

	MassSpawner->SpawnEntities(EntityTemplate, 1, NewEntityHandles);
	for(auto& EntityHandle : NewEntityHandles) {
		EntityManager.AddFragmentToEntity(
			EntityHandle,
			FEcsactEntityFragment::StaticStruct(),
			[Entity](void* fragment, const UScriptStruct& FragmentType) {
				FEcsactEntityFragment* EntityFragment =
					static_cast<FEcsactEntityFragment*>(fragment);
				EntityFragment->SetId(static_cast<ecsact_entity_id>(Entity));
			}
		);
		auto* TransformFragment =
			EntityManager.GetFragmentDataPtr<FTransformFragment>(EntityHandle);

		auto vec = FVector{};
		vec.X = Position.X;
		vec.Y = Position.Y;
		vec.Z = Position.Z;

		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Entity Manager spawning entity at %f %f"),
			Position.X,
			Position.Y
		);
		auto Transform = FTransform(vec);
		TransformFragment->SetTransform(Transform);
	}
	EntityHandles += NewEntityHandles;

	EntityPools.Remove(Entity);
}
