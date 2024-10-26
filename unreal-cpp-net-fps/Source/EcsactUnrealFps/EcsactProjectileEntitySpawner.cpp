#include "EcsactProjectileEntitySpawner.h"
#include "EcsactUnrealFpsProjectile.h"
#include "EcsactUnreal/EcsactAsyncRunner.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

auto UEcsactProjectileEntitySpawner::CreateInitialEntities( //
	UEcsactRunner* Runner
) -> void {
	UE_LOG(LogTemp, Log, TEXT("Create Initial Entities"));

	// NOTE: For demonstration purposes only we're creating an entity for the
	// player right away. In a real multiplayer game your players will likely not
	// have permission to just create entities at will. Instead they will already
	// be created for them and any entity creation at runtime would occur during a
	// generator system of backend function. Refer to your Ecsact async
	// implemtnation for details.
	Runner->CreateEntity()
		.AddComponent(example::fps::Player{})
		.AddComponent(example::fps::Position{})
		.AddComponent(example::fps::Rotation{});
}

auto UEcsactProjectileEntitySpawner::RunnerStart_Implementation( //
	class UEcsactRunner* Runner
) -> void {
	auto async_runner = Cast<UEcsactAsyncRunner>(Runner);
	if(async_runner) {
		async_runner->OnConnect(TDelegate<void()>::CreateLambda([this, Runner] {
			CreateInitialEntities(Runner);
		}));
	} else {
		CreateInitialEntities(Runner);
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
	auto projectile = world->SpawnActor( //
		ProjectileClass,
		&pos,
		&rot,
		spawn_params
	);

	if(projectile) {
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
