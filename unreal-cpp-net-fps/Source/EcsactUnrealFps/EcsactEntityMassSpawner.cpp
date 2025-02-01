#include "EcsactEntityMassSpawner.h"

#include "Components/SkeletalMeshComponent.h"
#include "MassCommands.h"
#include "MassRepresentationActorManagement.h"
#include "EcsactUnrealFps/EcsactUnrealFps.ecsact.hh"
#include "EcsactUnrealFps/EcsactUnrealFps__ecsact__ue.h"
#include "MassSpawnerSubsystem.h"
#include "MassEntitySubsystem.h"
#include "MassActorSubsystem.h"
#include "MassEntityTemplateRegistry.h"
#include "MassEntityManager.h"
#include "Enemy.h"
#include "MassCommonFragments.h"
#include "Engine/SkeletalMesh.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "Fragments/EcsactFragments.h"
#include "EcsactUnrealFps.ecsact.hh"

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
	auto runner = EcsactUnrealExecution::Runner(world).Get();
	if(runner) {
		for(auto subsystem : runner->GetSubsystemArray<ThisClass>()) {
			if(subsystem) {
				return subsystem->StreamEntities;
			}
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

auto UEcsactEntityMassSpawner::GetEntityMassConfig() const
	-> UMassEntityConfigAsset* {
	if(!StreamEntities && MassEntityConfigAsset) {
		return MassEntityConfigAsset;
	}

	return StreamingMassEntityConfigAsset;
}

auto UEcsactEntityMassSpawner::InitEnemy_Implementation(
	int32            Entity,
	FExampleFpsEnemy Enemy
) -> void {
	Super::InitEnemy_Implementation(Entity, Enemy);
	auto* world = GetWorld();

	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	auto mass_actor_subsystem = world->GetSubsystem<UMassActorSubsystem>();

	for(auto entity_handle : entity_handles) {
		auto entity_actor = mass_actor_subsystem->GetActorFromHandle(entity_handle);
		if(!entity_actor) {
			return;
		}
		auto enemy_entity_actor = Cast<AEnemy>(entity_actor);
		if(!enemy_entity_actor) {
			return;
		}

		enemy_entity_actor->OnInitEnemy(Enemy);
	}
}

auto UEcsactEntityMassSpawner::RemoveEnemy_Implementation(
	int32            Entity,
	FExampleFpsEnemy Enemy
) -> void {
	Super::RemoveEnemy_Implementation(Entity, Enemy);

	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	auto mass_actor_subsystem = GetWorld()->GetSubsystem<UMassActorSubsystem>();

	for(auto entity_handle : entity_handles) {
		auto entity_actor = mass_actor_subsystem->GetActorFromHandle(entity_handle);
		if(!entity_actor) {
			continue;
		}
		auto enemy_entity_actor = Cast<AEnemy>(entity_actor);
		if(!enemy_entity_actor) {
			continue;
		}

		enemy_entity_actor->OnRemoveEnemy(Enemy);
	}
}

auto UEcsactEntityMassSpawner::InitPosition_Implementation(
	int32               Entity,
	FExampleFpsPosition Position
) -> void {
	Super::InitPosition_Implementation(Entity, Position);

	auto& entity_manager =
		GetWorld()->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
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

auto UEcsactEntityMassSpawner::InitRotation_Implementation(
	int32               Entity,
	FExampleFpsRotation Rotation
) -> void {
	Super::InitRotation_Implementation(Entity, Rotation);

	auto& entity_manager =
		GetWorld()->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		entity_manager.Defer().PushCommand<FMassDeferredSetCommand>(
			[entity_handle, Rotation](FMassEntityManager& entity_manager) {
				entity_manager.GetFragmentDataPtr<FTransformFragment>(entity_handle)
					->GetMutableTransform()
					.SetRotation(FQuat::MakeFromEuler(FVector{
						Rotation.Roll,
						Rotation.Pitch,
						Rotation.Yaw,
					}));
			}
		);
	}
}

auto UEcsactEntityMassSpawner::ToggleStreamTag(
	int32             Entity,
	FExampleFpsToggle Toggle
) -> void {
	auto& entity_manager =
		GetWorld()->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	auto entity_handles = GetEcsactMassEntityHandles(Entity);
	for(auto entity_handle : entity_handles) {
		if(Toggle.Streaming) {
			entity_manager.Defer().AddTag<FEcsactStreamTag>(entity_handle);
		} else {
			entity_manager.Defer().RemoveTag<FEcsactStreamTag>(entity_handle);
		}
	}
}

auto UEcsactEntityMassSpawner::InitToggle_Implementation( //
	int32             Entity,
	FExampleFpsToggle Toggle
) -> void {
	Super::InitToggle_Implementation(Entity, Toggle);

	if(!StreamEntities) {
		return;
	}

	ToggleStreamTag(Entity, Toggle);
}

auto UEcsactEntityMassSpawner::UpdateToggle_Implementation( //
	int32             Entity,
	FExampleFpsToggle Toggle
) -> void {
	Super::UpdateToggle_Implementation(Entity, Toggle);

	if(!StreamEntities) {
		return;
	}

	ToggleStreamTag(Entity, Toggle);
}

auto UEcsactEntityMassSpawner::InitStunned_Implementation( //
	int32              Entity,
	FExampleFpsStunned Stunned
) -> void {
	Super::InitStunned_Implementation(Entity, Stunned);

	auto mass_actor_subsystem = GetWorld()->GetSubsystem<UMassActorSubsystem>();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);

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
	Super::UpdateStunned_Implementation(Entity, Stunned);

	auto mass_actor_subsystem = GetWorld()->GetSubsystem<UMassActorSubsystem>();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);

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
	Super::RemoveStunned_Implementation(Entity, Stunned);

	auto mass_actor_subsystem = GetWorld()->GetSubsystem<UMassActorSubsystem>();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);

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
		skeletal_mesh->SetSimulatePhysics(false);

		enemy_entity_actor->OnRemoveStunned(Stunned);
	}
}

auto UEcsactEntityMassSpawner::InitPushing_Implementation( //
	int32              Entity,
	FExampleFpsPushing Pushing
) -> void {
	Super::InitPushing_Implementation(Entity, Pushing);

	auto mass_actor_subsystem = GetWorld()->GetSubsystem<UMassActorSubsystem>();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);

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
		skeletal_mesh->SetSimulatePhysics(true);
	}
}

auto UEcsactEntityMassSpawner::UpdateEnemy_Implementation( //
	int32            Entity,
	FExampleFpsEnemy Enemy
) -> void {
	Super::UpdateEnemy_Implementation(Entity, Enemy);

	auto mass_actor_subsystem = GetWorld()->GetSubsystem<UMassActorSubsystem>();
	auto entity_handles = GetEcsactMassEntityHandles(Entity);

	for(auto entity_handle : entity_handles) {
		auto entity_actor = mass_actor_subsystem->GetActorFromHandle(entity_handle);
		if(!entity_actor) {
			continue;
		}
		auto enemy_entity_actor = Cast<AEnemy>(entity_actor);
		if(!enemy_entity_actor) {
			continue;
		}

		enemy_entity_actor->OnUpdateEnemy(Enemy);
	}
}
