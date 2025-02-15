#pragma once

#include "CoreMinimal.h"
#include "Basic/Basic__ecsact__ue.h"
#include "CounterSubsystem.generated.h"

UCLASS(BlueprintType)
class UCounterSubsystem : public UBasicEcsactRunnerSubsystem {
	GENERATED_BODY() // nolint

	TMap<int32, int32> AllCounts;

public:
	/**
	 * Convenient function to access counter total anywhere
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "Ecsact Basic Example",
		Meta = (WorldContext = "WorldContext")
	)
	static int32 GetCounterTotal(UObject* WorldContext);

	auto RunnerStart_Implementation(UEcsactRunner* Runner) -> void override;
	auto InitCount_Implementation(int32 Entity, FBasicCount Count) -> void override;
	auto UpdateCount_Implementation(int32 Entity, FBasicCount Count) -> void override;
	auto RemoveCount_Implementation(int32 Entity, FBasicCount Count) -> void override;
};
