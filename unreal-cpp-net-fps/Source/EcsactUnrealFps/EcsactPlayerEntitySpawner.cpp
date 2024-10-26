#include "EcsactPlayerEntitySpawner.h"
#include "EcsactUnrealFps/EcsactUnrealFpsCharacter.h"
#include "EcsactUnrealFpsGameMode.h"
#include "EcsactUnreal/EcsactAsyncRunner.h"
#include "EcsactUnreal/EcsactSyncRunner.h"
#include "EcsactUnrealFpsPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ecsact/runtime/dynamic.h"

auto UEcsactPlayerEntitySpawner::RunnerStart_Implementation( //
	UEcsactRunner* Runner
) -> void {
}

auto UEcsactPlayerEntitySpawner::InitPlayer_Implementation(
	int32             Entity,
	FExampleFpsPlayer Player
) -> void {
	auto& controller = AssignedControllers.Add(Entity);

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Looking for available controller for entity %i"),
		Entity
	);
	while(!PendingControllers.IsEmpty()) {
		controller = PendingControllers.Pop();
		if(controller.IsValid()) {
			SetupController(Entity, controller.Get());
			return;
		}
	}

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("No controller found for entity %i. adding proxy actor instead."),
		Entity
	);

	auto* Actor = GetWorld()->SpawnActor<AActor>(
		ProxyPlayerClass,
		SpawnLocation,
		SpawnRotator
	);

	check(Actor);
	PlayerEntities.Add(Entity, Actor);
}

auto UEcsactPlayerEntitySpawner::RemovePlayer_Implementation(
	int32             Entity,
	FExampleFpsPlayer Player
) -> void {
	PlayerEntities.Remove(Entity);
	// TODO
}

auto UEcsactPlayerEntitySpawner::SetupController(
	int32                             Entity,
	AEcsactUnrealFpsPlayerController* Controller
) -> void {
	UE_LOG(LogTemp, Warning, TEXT("Setup Controller (Entity=%i)"), Entity);

	check(Controller);
	auto spawn_params = FActorSpawnParameters{};
	spawn_params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	auto* world = Controller->GetWorld();
	check(world);
	auto* game_mode = UGameplayStatics::GetGameMode(world);
	check(game_mode);
	auto player_start = game_mode->FindPlayerStart(Controller);
	check(player_start);
	auto* pawn = world->SpawnActor<AEcsactUnrealFpsCharacter>(
		game_mode->DefaultPawnClass,
		player_start->GetActorLocation(),
		player_start->GetActorRotation(),
		spawn_params
	);
	check(pawn);
	// TODO: no cast please
	pawn->CharacterEntity = static_cast<ecsact_entity_id>(Entity);
	PlayerEntities.Add(Entity, pawn);
	Controller->Possess(pawn);
}

auto UEcsactPlayerEntitySpawner::AddPlayerController( //
	class AEcsactUnrealFpsPlayerController* Controller
) -> void {
	check(Controller);
	for(auto& entry : AssignedControllers) {
		if(!entry.Value.IsValid()) {
			entry.Value = Controller;
			SetupController(entry.Key, Controller);
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Adding pending player controller"));
	PendingControllers.Add(Controller);
}

auto UEcsactPlayerEntitySpawner::RemovePlayerController( //
	class AEcsactUnrealFpsPlayerController* Controller
) -> void {
	check(Controller);
	UE_LOG(LogTemp, Warning, TEXT("Removing pending player controller"));
	PendingControllers.Remove(Controller);
}

auto UEcsactPlayerEntitySpawner::UpdatePosition_Implementation( //
	int32               Entity,
	FExampleFpsPosition Position
) -> void {
	auto result = AssignedControllers.Find(Entity);

	if(result) {
		return;
	}
	auto ActorWeakPtr = PlayerEntities.Find(Entity);

	if(!ActorWeakPtr) {
		return;
	}

	if(ActorWeakPtr->IsValid()) {
		auto* actor = ActorWeakPtr->Get();
		// UE_LOG(
		// 	LogTemp,
		// 	Error,
		// 	TEXT("Entity %i Pos %f %f %f"),
		// 	Entity,
		// 	Position.X,
		// 	Position.Y,
		// 	Position.Z
		// );
		actor->SetActorLocation(FVector{Position.X, Position.Y, Position.Z});
	} else {
		UE_LOG(LogTemp, Warning, TEXT("The found player controller is invalid"));
	}
}
