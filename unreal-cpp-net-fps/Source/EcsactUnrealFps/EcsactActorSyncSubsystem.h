#pragma once

#include "CoreMinimal.h"
#include "ecsact/runtime/common.h"
#include "EcsactUnrealFps__ecsact__ue.h"
#include "EcsactActorSyncSubsystem.generated.h"

UCLASS()

class UEcsactActorSyncSubsystem : public UExampleFpsEcsactRunnerSubsystem {
	GENERATED_BODY() // NOLINT

	TMap<ecsact_entity_id, TWeakObjectPtr<class UEcsactActor>> EntityActors = {};

public:
	auto RunnerStart_Implementation( //
		class UEcsactRunner* Runner
	) -> void override;

	auto UpdatePosition_Implementation( //
		int32               Entity,
		FExampleFpsPosition Position
	) -> void override;

	auto RegisterEcsactActor( //
		ecsact_entity_id                   Entity,
		TWeakObjectPtr<class UEcsactActor> EcsactActor
	) -> void;

	auto DeregisterEcsactActor( //
		ecsact_entity_id                   Entity,
		TWeakObjectPtr<class UEcsactActor> EcsactActor
	) -> void;
};
