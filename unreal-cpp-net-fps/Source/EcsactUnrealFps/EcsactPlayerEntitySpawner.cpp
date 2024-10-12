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

	if(!PendingControllers.IsEmpty()) {
		controller = PendingControllers.Pop();
		SetupController(Entity, controller.Get());
	}
}

auto UEcsactPlayerEntitySpawner::RemovePlayer_Implementation(
	int32             Entity,
	FExampleFpsPlayer Player
) -> void {
	// TODO
}

auto UEcsactPlayerEntitySpawner::SetupController(
	int32                             Entity,
	AEcsactUnrealFpsPlayerController* Controller
) -> void {
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
	Controller->Possess(pawn);
}

auto UEcsactPlayerEntitySpawner::AddPlayerController( //
	class AEcsactUnrealFpsPlayerController* Controller
) -> void {
	check(Controller);
	for(auto& entry : AssignedControllers) {
		if(entry.Value == nullptr) {
			entry.Value = Controller;
			SetupController(entry.Key, Controller);
			return;
		}
	}

	PendingControllers.Add(Controller);
}
