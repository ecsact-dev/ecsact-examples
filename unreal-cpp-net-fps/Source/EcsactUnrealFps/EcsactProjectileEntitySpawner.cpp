#include "EcsactProjectileEntitySpawner.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

auto UEcsactProjectileEntitySpawner::InitProjectile_Implementation(
	int32                 Entity,
	FExampleFpsProjectile Projectile
) -> void {
	auto world = GetWorld();
	check(world);
	auto spawn_params = FActorSpawnParameters{};
	spawn_params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	static auto projectile_class = //
		ConstructorHelpers::FClassFinder<AActor>{
			TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonProjectile"),
		};

	auto pos = FVector{};
	auto rot = FRotator{};
	auto projectile = world->SpawnActor( //
		projectile_class.Class.Get(),
		&pos,
		&rot,
		spawn_params
	);
	ProjectileActors.Add(Entity, projectile);

	UE_LOG(LogTemp, Warning, TEXT("Spawning Projectile!"));
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
		TEXT("Entity %i Pos %f %f %f"),
		Entity,
		Position.X,
		Position.Y,
		Position.Z
	);
}
