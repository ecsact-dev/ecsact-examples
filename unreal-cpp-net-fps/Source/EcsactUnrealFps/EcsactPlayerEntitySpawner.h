#pragma once

#include "CoreMinimal.h"
#include "EcsactUnrealFps__ecsact__ue.h"
#include "EcsactPlayerEntitySpawner.generated.h"

UCLASS()

class UEcsactPlayerEntitySpawner : public UExampleFpsEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT

	TArray<class AEcsactUnrealFpsPlayerController*>      PendingControllers = {};
	TMap<int32, class AEcsactUnrealFpsPlayerController*> AssignedControllers = {};

	auto OnAsyncConnected() -> void;
	auto CreateInitialEntities() -> void;
	auto SetupController(
		int32                                   Entity,
		class AEcsactUnrealFpsPlayerController* Controller
	) -> void;

public:
	auto RunnerStart_Implementation( //
		class UEcsactRunner* Runner
	) -> void override;

	auto InitPlayer_Implementation( //
		int32             Entity,
		FExampleFpsPlayer Player
	) -> void override;
	auto RemovePlayer_Implementation( //
		int32             Entity,
		FExampleFpsPlayer Player
	) -> void override;

	/**
	 * Adds a player controller that will be considered when an entity with a
	 * player tag is created
	 */
	auto AddPlayerController( //
		class AEcsactUnrealFpsPlayerController* Controller
	) -> void;
};
