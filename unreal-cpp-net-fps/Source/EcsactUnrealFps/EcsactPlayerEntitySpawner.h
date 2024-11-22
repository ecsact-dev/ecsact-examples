#pragma once

#include "CoreMinimal.h"
#include "EcsactUnrealFps__ecsact__ue.h"
#include "EcsactPlayerEntitySpawner.generated.h"

UCLASS(Abstract)

class UEcsactPlayerEntitySpawner : public UExampleFpsEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT

	auto CreateInitialEntities(class UEcsactRunner* Runner) -> void;

	TArray<TWeakObjectPtr<class AEcsactUnrealFpsPlayerController>>
		PendingControllers = {};
	TMap<int32, TWeakObjectPtr<class AEcsactUnrealFpsPlayerController>>
		AssignedControllers = {};

	TMap<int32, FExampleFpsPlayer> EntityPlayerStructs;

	auto SetupController(
		int32                                   Entity,
		FExampleFpsPlayer                       Player,
		class AEcsactUnrealFpsPlayerController* Controller
	) -> void;

public:
	UFUNCTION(
		BlueprintCallable,
		Category = "Ecsact Net Unreal Example",
		Meta = (WorldContext = "WorldContext")
	)
	static void SetLocalEcsactPlayerId(
		const UObject* WorldContext,
		int32          NewPlayerId
	);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LocallyControllerPlayerId = 0;

	TMap<int32, TWeakObjectPtr<AActor>> PlayerEntities;

	auto GetPlayerPosition(ecsact_entity_id Entity) -> FVector;

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

	auto InitPusher_Implementation( //
		int32             Entity,
		FExampleFpsPusher Pusher
	) -> void override;

	auto RemovePusher_Implementation( //
		int32             Entity,
		FExampleFpsPusher Pusher
	) -> void override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProxyPlayerClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PushEffectClass;

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
