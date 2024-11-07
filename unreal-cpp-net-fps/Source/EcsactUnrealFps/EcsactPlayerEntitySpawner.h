#pragma once

#include "CoreMinimal.h"
#include "EcsactUnrealFps__ecsact__ue.h"
#include "EcsactPlayerEntitySpawner.generated.h"

UCLASS()

class UEcsactPlayerEntitySpawner : public UExampleFpsEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT

	auto CreateInitialEntities(class UEcsactRunner* Runner) -> void;

	TArray<TWeakObjectPtr<class AEcsactUnrealFpsPlayerController>>
		PendingControllers = {};
	TMap<int32, TWeakObjectPtr<class AEcsactUnrealFpsPlayerController>>
		AssignedControllers = {};

	auto SetupController(
		int32                                   Entity,
		class AEcsactUnrealFpsPlayerController* Controller
	) -> void;

public:
	TMap<int32, TWeakObjectPtr<AActor>> PlayerEntities;

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

	auto UpdatePosition_Implementation( //
		int32               Entity,
		FExampleFpsPosition Position
	) -> void override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProxyPlayerClass;

	UPROPERTY(EditAnywhere)
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere)
	FRotator SpawnRotator;
	/**
	 * Adds a player controller that will be considered when an entity with a
	 * player tag is created
	 */
	auto AddPlayerController( //
		class AEcsactUnrealFpsPlayerController* Controller
	) -> void;

	auto RemovePlayerController( //
		class AEcsactUnrealFpsPlayerController* Controller
	) -> void;
};
