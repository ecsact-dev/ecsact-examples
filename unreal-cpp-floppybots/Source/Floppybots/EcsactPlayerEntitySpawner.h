#pragma once

#include "CoreMinimal.h"
#include "EcsactUnreal/EcsactAsyncRunnerEvents.h"
#include "Floppybots__ecsact__ue.h"
#include "EcsactPlayerEntitySpawner.generated.h"

class AFloppybotsCharacter;

UCLASS(Abstract)

class UEcsactPlayerEntitySpawner : public UFloppybotsEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT

	auto CreateInitialEntities(class UEcsactRunner* Runner) -> void;

	TArray<TWeakObjectPtr<class AFloppybotsPlayerController>> PendingControllers = {};
	TMap<int32, TWeakObjectPtr<class AFloppybotsPlayerController>>
		AssignedControllers = {};

	TMap<int32, FFloppybotsPlayer> EntityPlayerStructs;

	auto SetupController(
		int32 Entity,
		FFloppybotsPlayer Player,
		class AFloppybotsPlayerController* Controller
	) -> void;

public:
	UFUNCTION(
		BlueprintCallable,
		Category = "Ecsact Net Unreal Example",
		Meta = (WorldContext = "WorldContext")
	)
	static void SetLocalEcsactPlayerId(
		const UObject* WorldContext,
		int32 NewPlayerId
	);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LocallyControllerPlayerId = 0;

	TMap<int32, TWeakObjectPtr<AFloppybotsCharacter>> PlayerEntities;

	auto GetPlayerPosition(ecsact_entity_id Entity) -> FVector;

	auto RunnerStart_Implementation( //
		class UEcsactRunner* Runner
	) -> void override;

	auto InitPlayer_Implementation( //
		int32 Entity,
		FFloppybotsPlayer Player
	) -> void override;
	auto RemovePlayer_Implementation( //
		int32 Entity,
		FFloppybotsPlayer Player
	) -> void override;

	auto InitPosition_Implementation( //
		int32 Entity,
		FFloppybotsPosition Position
	) -> void override;

	auto UpdatePosition_Implementation( //
		int32 Entity,
		FFloppybotsPosition Position
	) -> void override;

	auto UpdateMovedirection_Implementation( //
		int32 Entity,
		FFloppybotsMovedirection MoveDirection
	) -> void override;

	auto InitPusher_Implementation( //
		int32 Entity,
		FFloppybotsPusher Pusher
	) -> void override;

	auto RemovePusher_Implementation( //
		int32 Entity,
		FFloppybotsPusher Pusher
	) -> void override;

	auto InitPushcharge_Implementation(
		int32 Entity,
		FFloppybotsPushcharge Pushcharge
	) -> void override;

	auto UpdatePushcharge_Implementation(
		int32 Entity,
		FFloppybotsPushcharge Pushcharge
	) -> void override;

	auto RemovePushcharge_Implementation(
		int32 Entity,
		FFloppybotsPushcharge Pushcharge
	) -> void override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFloppybotsCharacter> ProxyPlayerClass;

	UPROPERTY(EditAnywhere)
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere)
	FRotator SpawnRotator;
	/**
	 * Adds a player controller that will be considered when an entity with a
	 * player tag is created
	 */
	auto AddPlayerController( //
		class AFloppybotsPlayerController* Controller
	) -> void;

	auto RemovePlayerController( //
		class AFloppybotsPlayerController* Controller
	) -> void;
};
