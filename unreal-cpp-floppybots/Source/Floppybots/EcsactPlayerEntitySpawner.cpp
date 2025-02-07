#include "EcsactPlayerEntitySpawner.h"
#include "EcsactUnreal/EcsactAsyncRunnerEvents.h"
#include "Floppybots/FloppybotsCharacter.h"
#include "EcsactUnreal/EcsactExecution.h"
#include "Floppybots/Fragments/FollowPlayerTargetFragment.h"
#include "FloppybotsGameMode.h"
#include "EcsactUnreal/EcsactAsyncRunner.h"
#include "EcsactUnreal/EcsactSyncRunner.h"
#include "FloppybotsPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FloppybotsCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MassEntitySubsystem.h"
#include "MassSpawnerSubsystem.h"
#include "ecsact/runtime/common.h"

auto UEcsactPlayerEntitySpawner::CreateInitialEntities( //
	UEcsactRunner* Runner
) -> void {
	UE_LOG(LogTemp, Log, TEXT("Create Initial Entities"));

	// NOTE: For demonstration purposes only we're creating an entity for the
	// player right away. In a real multiplayer game your players will likely not
	// have permission to just create entities at will. Instead they will already
	// be created for them and any entity creation at runtime would occur during a
	// generator system of backend function. Refer to your Ecsact async
	// implemenation for details.
	Runner->CreateEntity()
		.AddComponent(floppybots::Player{LocallyControllerPlayerId})
		.AddComponent(floppybots::MoveDirection{})
		.AddComponent(floppybots::Position{})
		.AddComponent(floppybots::Rotation{});
}

auto UEcsactPlayerEntitySpawner::GetPlayerPosition( //
	ecsact_entity_id Entity
) -> FVector {
	auto controller = AssignedControllers.Find(static_cast<int32>(Entity));
	if(controller && controller->IsValid()) {
		return controller->Get()->GetPawn()->GetActorLocation();
	}

	auto proxy = PlayerEntities.Find(static_cast<int32>(Entity));
	if(proxy && proxy->IsValid()) {
		return proxy->Get()->GetActorLocation();
	}

	return {};
}

auto UEcsactPlayerEntitySpawner::SetLocalEcsactPlayerId( //
	const UObject* WorldContext,
	int32          NewPlayerId
) -> void {
	auto world = WorldContext->GetWorld();
	if(!world) {
		UE_LOG(
			LogTemp,
			Error,
			TEXT("SetLocalEcsactPlayerId called too early - world not ready")
		);
		return;
	}
	auto runner = EcsactUnrealExecution::Runner(world).Get();
	if(!runner) {
		UE_LOG(
			LogTemp,
			Error,
			TEXT("SetLocalEcsactPlayerId called too early - runner not ready")
		);
		return;
	}

	auto self = runner->GetSubsystem<ThisClass>();
	if(!self) {
		UE_LOG(
			LogTemp,
			Error,
			TEXT("SetLocalEcsactPlayerId called too early - player entity spawner "
					 "not ready")
		);
		return;
	}

	self->LocallyControllerPlayerId = NewPlayerId;

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Setting new locally controlled player id %i"),
		NewPlayerId
	);
}

auto UEcsactPlayerEntitySpawner::RunnerStart_Implementation( //
	UEcsactRunner* Runner
) -> void {
	auto async_runner = Cast<UEcsactAsyncRunner>(Runner);
	if(async_runner) {
		async_runner->AsyncSessionEvent.AddWeakLambda(
			this,
			[this, Runner](int32, EEcsactAsyncSessionEvent event) {
				if(event == EEcsactAsyncSessionEvent::Started) {
					CreateInitialEntities(Runner);
				}
			}
		);
	} else {
		CreateInitialEntities(Runner);
	}
}

auto UEcsactPlayerEntitySpawner::InitPlayer_Implementation(
	int32             Entity,
	FFloppybotsPlayer Player
) -> void {
	UE_LOG(LogTemp, Log, TEXT("InitPlayer"));
	EntityPlayerStructs.FindOrAdd(Entity) = Player;

	if(Player.PlayerId == LocallyControllerPlayerId) {
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
				SetupController(Entity, Player, controller.Get());
				return;
			}
		}
	}

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("No controller found for entity %i. adding proxy actor instead."),
		Entity
	);

	if(ProxyPlayerClass) {
		auto spawn_params = FActorSpawnParameters{};
		spawn_params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		auto* proxy_character = GetWorld()->SpawnActor<AFloppybotsCharacter>(
			ProxyPlayerClass,
			SpawnLocation,
			SpawnRotator,
			spawn_params
		);

		proxy_character->OnInitPlayer(Player);

		check(proxy_character);
		PlayerEntities.Add(Entity, proxy_character);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("ProxyPlayerClass is unset"));
	}
}

auto UEcsactPlayerEntitySpawner::RemovePlayer_Implementation(
	int32             Entity,
	FFloppybotsPlayer Player
) -> void {
	PlayerEntities.Remove(Entity);
	EntityPlayerStructs.Remove(Entity);
	// TODO
}

auto UEcsactPlayerEntitySpawner::SetupController(
	int32                        Entity,
	FFloppybotsPlayer            Player,
	AFloppybotsPlayerController* Controller
) -> void {
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Setup Controller (Entity=%i PlayerId=%i)"),
		Entity,
		Player.PlayerId
	);

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
	auto* pawn = world->SpawnActor<AFloppybotsCharacter>(
		game_mode->DefaultPawnClass,
		player_start->GetActorLocation(),
		player_start->GetActorRotation(),
		spawn_params
	);
	pawn->OnInitPlayer(Player);
	check(pawn);
	// TODO: no cast please
	pawn->CharacterEntity = static_cast<ecsact_entity_id>(Entity);
	pawn->CharacterPlayerId = Player.PlayerId;
	PlayerEntities.Add(Entity, pawn);
	Controller->Possess(pawn);
}

auto UEcsactPlayerEntitySpawner::AddPlayerController( //
	class AFloppybotsPlayerController* Controller
) -> void {
	check(Controller);
	for(auto& entry : AssignedControllers) {
		if(!entry.Value.IsValid()) {
			entry.Value = Controller;
			auto player = EntityPlayerStructs.FindChecked(entry.Key);
			if(player.PlayerId == LocallyControllerPlayerId) {
				SetupController(
					entry.Key,
					EntityPlayerStructs.FindChecked(entry.Key),
					Controller
				);
				return;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Adding pending player controller"));
	PendingControllers.Add(Controller);
}

auto UEcsactPlayerEntitySpawner::RemovePlayerController( //
	class AFloppybotsPlayerController* Controller
) -> void {
	check(Controller);
	UE_LOG(LogTemp, Warning, TEXT("Removing pending player controller"));
	PendingControllers.Remove(Controller);
}

auto UEcsactPlayerEntitySpawner::InitPosition_Implementation( //
	int32               Entity,
	FFloppybotsPosition Position
) -> void {
	UpdatePosition_Implementation(Entity, Position);
}

auto UEcsactPlayerEntitySpawner::UpdatePosition_Implementation( //
	int32               Entity,
	FFloppybotsPosition Position
) -> void {
	auto itr = PlayerEntities.Find(Entity);
	if(!itr) {
		return;
	}

	auto player = itr->Get();
	if(!player) {
		return;
	}

	if(!player->Controller) {
		auto desired_location = FVector{Position.X, Position.Y, Position.Z};
		player->SetActorLocation(desired_location);
	}

	auto* world = GetWorld();
	auto& entity_manager =
		world->GetSubsystem<UMassEntitySubsystem>()->GetMutableEntityManager();

	entity_manager.ForEachSharedFragment<FFollowPlayerTargetFragment>(
		[&](FFollowPlayerTargetFragment& f) {
			f.SetPlayerPosition(
				Entity,
				FVector{
					Position.X,
					Position.Y,
					Position.Z,
				}
			);
		}
	);
}

auto UEcsactPlayerEntitySpawner::UpdateMovedirection_Implementation( //
	int32                    Entity,
	FFloppybotsMovedirection MoveDirection
) -> void {
	auto itr = PlayerEntities.Find(Entity);
	if(!itr) {
		return;
	}

	auto player = itr->Get();
	if(!player) {
		return;
	}

	// Only set the move direction if they don't have a controller. If they have a
	// controller they are being controlled locally and are handling the move
	// direction themselves.
	if(!player->Controller) {
		player->SetMoveDirection(MoveDirection.X, MoveDirection.Y);
	}
}

auto UEcsactPlayerEntitySpawner::InitPusher_Implementation( //
	int32             Entity,
	FFloppybotsPusher Pusher
) -> void {
	UE_LOG(LogTemp, Warning, TEXT("Init Pusher"));
}

auto UEcsactPlayerEntitySpawner::RemovePusher_Implementation( //
	int32             Entity,
	FFloppybotsPusher Pusher
) -> void {
	UE_LOG(LogTemp, Warning, TEXT("Remove Pusher"));
}

auto UEcsactPlayerEntitySpawner::InitPushcharge_Implementation(
	int32                 Entity,
	FFloppybotsPushcharge Pushcharge
) -> void {
	auto itr = PlayerEntities.Find(Entity);
	if(!itr) {
		return;
	}

	auto player = itr->Get();
	if(!player) {
		return;
	}

	player->OnInitPushcharge(Pushcharge);
}

auto UEcsactPlayerEntitySpawner::UpdatePushcharge_Implementation(
	int32                 Entity,
	FFloppybotsPushcharge Pushcharge
) -> void {
	auto itr = PlayerEntities.Find(Entity);
	if(!itr) {
		return;
	}

	auto player = itr->Get();
	if(!player) {
		return;
	}
	player->OnUpdatePushcharge(Pushcharge);
}

auto UEcsactPlayerEntitySpawner::RemovePushcharge_Implementation(
	int32                 Entity,
	FFloppybotsPushcharge Pushcharge
) -> void {
	auto itr = PlayerEntities.Find(Entity);
	if(!itr) {
		return;
	}

	auto player = itr->Get();
	if(!player) {
		return;
	}
	player->OnRemovePushcharge(Pushcharge);
}
