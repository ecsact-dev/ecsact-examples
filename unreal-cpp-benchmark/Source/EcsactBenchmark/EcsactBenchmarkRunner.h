#pragma once

#include "CoreMinimal.h"
#include "EcsactUnreal/EcsactRunner.h"
#include "ecsact/runtime/core.hh"

#include "EcsactBenchmarkRunner.generated.h"

UCLASS()

class ECSACTBENCHMARK_API UEcsactBenchmarkRunner : public UEcsactRunner {
	GENERATED_BODY()

	std::optional<ecsact::core::registry> registry;

	auto Start() -> void override;
	auto Stop() -> void override;
	auto Tick(float deltaTime) -> void override;

	bool should_run;
};
