#include "EcsactEntityMassSpawner.h"

#include "Components/SkeletalMeshComponent.h"
#include "MassCommands.h"
#include "MassMovementFragments.h"
#include "MassRepresentationActorManagement.h"
#include "MassStateTreeSubsystem.h"
#include "Math/Vector.h"
#include "EcsactUnrealFps/EcsactUnrealFps.ecsact.hh"
#include "EcsactUnrealFps/EcsactUnrealFps__ecsact__ue.h"
#include "MassEntityTemplate.h"
#include "MassSpawnerSubsystem.h"
#include "MassEntitySubsystem.h"
#include "MassActorSubsystem.h"
#include "MassEntityTemplateRegistry.h"
#include "MassActorSubsystem.h"
#include "MassEntityManager.h"
#include "Enemy.h"
#include "MassCommonFragments.h"
#include "Engine/SkeletalMesh.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "Fragments/EcsactFragments.h"
#include "EcsactUnrealFps.ecsact.hh"
#include "EcsactUnrealFps/Commands/UpdateCommands.h"

auto UEcsactEntityMassSpawner::SetStreamEntities(
	const UObject* WorldContext,
	bool           bStreamEntities
) -> void {
	auto world = WorldContext->GetWorld();
	check(world);
	auto runner = EcsactUnrealExecution::Runner(world);
	checkSlow(runner.IsValid());
	for(auto subsystem : runner->GetSubsystemArray<ThisClass>()) {
		if(subsystem) {
			subsystem->StreamEntities = bStreamEntities;
		}
	}
}

auto UEcsactEntityMassSpawner::IsStreamingEntities( //
	const UObject* WorldContext
) -> bool {
	auto world = WorldContext->GetWorld();
	check(world);
	auto runner = EcsactUnrealExecution::Runner(world);
	checkSlow(runner.IsValid());
	for(auto subsystem : runner->GetSubsystemArray<ThisClass>()) {
		if(subsystem) {
			return subsystem->StreamEntities;
		}
	}

	return true;
}

auto UEcsactEntityMassSpawner::CreateMassEntities(int count) -> void {
	auto runner = GetRunner();
	check(runner);

	for(int i = 0; i < count; i++) {
		auto RandomPointX = FMath::RandRange(-2000, 2000);
		auto RandomPointY = FMath::RandRange(-2000, 2000);

		runner->CreateEntity()
			.AddComponent(example::fps::Position{
				.x = static_cast<float>(RandomPointX),
				.y = static_cast<float>(RandomPointY),
				.z = 0
			})
			.AddComponent(example::fps::Rotation{})
			.AddComponent(example::fps::Enemy{})
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

auto UEcsactEntityMassSpawner::GetEntityMassConfig() const
	-> UMassEntityConfigAsset* {
	if(!StreamEntities && MassEntityConfigAsset) {
		return MassEntityConfigAsset;
	}

	return StreamingMassEntityConfigAsset;
}

auto UEcsactEntityMassSpawner::EntityCreated_Implementation( //
	int32 Entity
) -> void {
	checkSlow(!MassEntities.Contains(static_cast<ecsact_entity_id>(Entity)));

	auto* world = GetWorld();

	const auto& entity_template =
		GetEntityMassConfig()->GetOrCreateEntityTemplate(*world);
	auto new_entity_handles = TArray<FMassEntityHandle>{};

	auto  mass_spawner = world->GetSubsystem<UMassSpawnerSubsystem>();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	UE_LOG(LogTemp, Log, TEXT("EntityCreated implementation %i"), Entity);

	mass_spawner->SpawnEntities(entity_template, 1, new_entity_handles);
	MassEntities.Add(static_cast<ecsact_entity_id>(Entity), new_entity_handles);
	for(auto entity_handle : new_entity_handles) {
		entity_manager.Defer().PushCommand<FMassCommandAddFragmentInstances>(
			entity_handle,
			FEcsactEntityFragment{static_cast<ecsact_entity_id>(Entity)}
		);
	}

	UE_LOG(
		LogTemp,
		Log,
		TEXT("EntityCreated implementation %i"),
		new_entity_handles.Num()
	);
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

	auto* world = GetWorld();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles =
		MassEntities.FindChecked(static_cast<ecsact_entity_id>(Entity));

	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().AddTag<FExampleEnemyTag>(entity_handle);
	}
}

auto UEcsactEntityMassSpawner::RemoveEnemy_Implementation(
	int32            Entity,
	FExampleFpsEnemy Enemy
) -> void {
	if(!CheckMassEntities(Entity, TEXT("RemoveEnemy"))) {
		return;
	}

	auto* world = GetWorld();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();
	auto entity_handles =
		MassEntities.FindChecked(static_cast<ecsact_entity_id>(Entity));

	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().RemoveTag<FExampleEnemyTag>(entity_handle);
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

		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>(
			[entity_handle, Position](FMassEntityManager& entity_manager) {
				entity_manager.GetFragmentDataPtr<FTransformFragment>(entity_handle)
					->GetMutableTransform()
					.SetLocation(FVector{
						Position.X,
						Position.Y,
						Position.Z,
					});
			}
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

auto UEcsactEntityMassSpawner::InitRotation_Implementation(
	int32               Entity,
	FExampleFpsRotation Rotation
) -> void {
	if(!CheckMassEntities(Entity, TEXT("InitRotation"))) {
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
			FEcsactRotationFragment{FVector{
				Rotation.Roll,
				Rotation.Pitch,
				Rotation.Yaw,
			}}
		);

		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>(
			[entity_handle, Rotation](FMassEntityManager& entity_manager) {
				entity_manager.GetFragmentDataPtr<FTransformFragment>(entity_handle)
					->GetMutableTransform()
					.SetLocation(FVector{
						Rotation.Roll,
						Rotation.Pitch,
						Rotation.Yaw,
					});
			}
		);
	}
}

auto UEcsactEntityMassSpawner::UpdateRotation_Implementation(
	int32               Entity,
	FExampleFpsRotation Rotation
) -> void {
	if(!CheckMassEntities(Entity, TEXT("UpdateRotation"))) {
		return;
	}

	auto* world = GetWorld();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	const auto& entity_handles =
		MassEntities.FindChecked(static_cast<ecsact_entity_id>(Entity));
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>(
			[entity_handle, Rotation](FMassEntityManager& entity_manager) {
				entity_manager
					.GetFragmentDataPtr<FEcsactRotationFragment>(entity_handle)
					->SetRotation(FVector{
						Rotation.Roll,
						Rotation.Pitch,
						Rotation.Yaw,
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

auto UEcsactEntityMassSpawner::InitStunned_Implementation( //
	int32              Entity,
	FExampleFpsStunned Stunned
) -> void {
	if(!CheckMassEntities(Entity, TEXT("InitStunned"))) {
		return;
	}

	auto mass_actor_subsystem = GetWorld()->GetSubsystem<UMassActorSubsystem>();
	auto entity_handles = MassEntities[static_cast<ecsact_entity_id>(Entity)];

	for(auto entity_handle : entity_handles) {
		auto entity_actor = mass_actor_subsystem->GetActorFromHandle(entity_handle);
		if(!entity_actor) {
			continue;
		}
		auto enemy_entity_actor = Cast<AEnemy>(entity_actor);
		if(!enemy_entity_actor) {
			continue;
		}

		enemy_entity_actor->OnInitStunned(Stunned);
	}
}

auto UEcsactEntityMassSpawner::UpdateStunned_Implementation( //
	int32              Entity,
	FExampleFpsStunned Stunned
) -> void {
	if(!CheckMassEntities(Entity, TEXT("UpdateStunned"))) {
		return;
	}

	auto mass_actor_subsystem = GetWorld()->GetSubsystem<UMassActorSubsystem>();
	auto entity_handles = MassEntities[static_cast<ecsact_entity_id>(Entity)];

	for(auto entity_handle : entity_handles) {
		auto entity_actor = mass_actor_subsystem->GetActorFromHandle(entity_handle);
		if(!entity_actor) {
			continue;
		}
		auto enemy_entity_actor = Cast<AEnemy>(entity_actor);
		if(!enemy_entity_actor) {
			continue;
		}

		enemy_entity_actor->OnUpdateStunned(Stunned);
	}
}

auto UEcsactEntityMassSpawner::RemoveStunned_Implementation( //
	int32              Entity,
	FExampleFpsStunned Stunned
) -> void {
	if(!CheckMassEntities(Entity, TEXT("RemoveStunned"))) {
		return;
	}

	auto mass_actor_subsystem = GetWorld()->GetSubsystem<UMassActorSubsystem>();
	auto entity_handles = MassEntities[static_cast<ecsact_entity_id>(Entity)];

	for(auto entity_handle : entity_handles) {
		auto entity_actor = mass_actor_subsystem->GetActorFromHandle(entity_handle);
		if(!entity_actor) {
			continue;
		}
		auto enemy_entity_actor = Cast<AEnemy>(entity_actor);
		if(!enemy_entity_actor) {
			continue;
		}

		auto skeletal_mesh =
			enemy_entity_actor->FindComponentByClass<USkeletalMeshComponent>();
		if(!skeletal_mesh) {
			continue;
		}
		UE_LOG(LogTemp, Log, TEXT("PHYSICS FALSE"));
		skeletal_mesh->SetSimulatePhysics(false);
		// skeletal_mesh->SetAllBodiesSimulatePhysics(false);
		// skeletal_mesh->SetAllBodiesBelowSimulatePhysics("Rig1", false);

		enemy_entity_actor->OnRemoveStunned(Stunned);
	}
}

auto UEcsactEntityMassSpawner::InitPushing_Implementation( //
	int32              Entity,
	FExampleFpsPushing Pushing
) -> void {
	UE_LOG(LogTemp, Log, TEXT("INIT PUSHING"));
	auto mass_actor_subsystem = GetWorld()->GetSubsystem<UMassActorSubsystem>();
	auto entity_handles = MassEntities[static_cast<ecsact_entity_id>(Entity)];

	for(auto entity_handle : entity_handles) {
		auto entity_actor = mass_actor_subsystem->GetActorFromHandle(entity_handle);
		if(!entity_actor) {
			continue;
		}
		auto skeletal_mesh =
			entity_actor->FindComponentByClass<USkeletalMeshComponent>();
		if(!skeletal_mesh) {
			continue;
		}
		UE_LOG(LogTemp, Log, TEXT("PHYSICS TRUE"));
		skeletal_mesh->SetSimulatePhysics(true);
		// skeletal_mesh->SetAllBodiesSimulatePhysics(true);
		// skeletal_mesh->SetAllBodiesBelowSimulatePhysics("Rig1", true);
	}
}

auto UEcsactEntityMassSpawner::RemovePushing_Implementation( //
	int32              Entity,
	FExampleFpsPushing Pushing
) -> void {
	UE_LOG(LogTemp, Log, TEXT("REMOVE PUSHING"));
	// auto mass_actor_subsystem =
	// GetWorld()->GetSubsystem<UMassActorSubsystem>(); auto entity_handles =
	// MassEntities[static_cast<ecsact_entity_id>(Entity)];
	//
	// for(auto entity_handle : entity_handles) {
	// 	auto entity_actor =
	// mass_actor_subsystem->GetActorFromHandle(entity_handle); if(!entity_actor)
	// { 		continue;
	// 	}
	// }
}
