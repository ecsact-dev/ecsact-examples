#include "EcsactProjectileEntitySpawner.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "EcsactUnrealFpsProjectile.h"
#include "EcsactUnreal/EcsactAsyncRunner.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

auto UEcsactProjectileEntitySpawner::CreateInitialEntities() -> void {
	auto runner = EcsactUnrealExecution::Runner();
	check(runner.IsValid());

	UE_LOG(LogTemp, Log, TEXT("Create Initial Entities"));

	// NOTE: For demonstration purposes only we're creating an entity for the
	// player right away. In a real multiplayer game your players will likely not
	// have permission to just create entities at will. Instead they will already
	// be created for them and any entity creation at runtime would occur during a
	// generator system of backend function. Refer to your Ecsact async
	// implemtnation for details.
	runner->CreateEntity()
		.AddComponent(example::fps::Player{})
		.AddComponent(example::fps::Position{})
		.AddComponent(example::fps::Rotation{})
		.OnCreate(TDelegate<void(ecsact_entity_id)>::CreateLambda([](auto entity) {
			UE_LOG(LogTemp, Warning, TEXT("Initial entity created %i"), entity);
		}));
}

auto UEcsactProjectileEntitySpawner::RunnerStart_Implementation( //
	class UEcsactRunner* Runner
) -> void {
	auto async_runner = Cast<UEcsactAsyncRunner>(Runner);
	if(async_runner) {
		async_runner->OnConnect(TDelegate<void()>::CreateLambda([this] {
			CreateInitialEntities();
		}));
	} else {
		CreateInitialEntities();
	}
}

auto UEcsactProjectileEntitySpawner::InitProjectile_Implementation(
	int32                 Entity,
	FExampleFpsProjectile Projectile
) -> void {
	auto world = GetWorld();
	check(world);
	auto spawn_params = FActorSpawnParameters{};
	spawn_params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto pos = FVector{};
	auto rot = FRotator{};
	auto projectile = world->SpawnActor<AEcsactUnrealFpsProjectile>( //
		ProjectileClass,
		pos,
		rot,
		spawn_params
	);

	if(projectile) {
		projectile->Entity = static_cast<ecsact_entity_id>(Entity);
		ProjectileActors.Add(Entity, projectile);
		UE_LOG(LogTemp, Warning, TEXT("Spawning Projectile!"));
	} else {
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn projectile"));
	}
}

auto UEcsactProjectileEntitySpawner::RemoveProjectile_Implementation( //
	int32                 Entity,
	FExampleFpsProjectile Projectile
) -> void {
}

auto UEcsactProjectileEntitySpawner::UpdatePosition_Implementation( //
	int32               Entity,
	FExampleFpsPosition Position
) -> void {
	if(!ProjectileActors.Contains(Entity)) {
		return;
	}

	UE_LOG(
		LogTemp,
		Error,
		TEXT("Projectile Entity %i Pos %f %f %f"),
		Entity,
		Position.X,
		Position.Y,
		Position.Z
	);
}
