#pragma once

#include "EcsactUnreal/EcsactRunner.h"
#include "FloppybotsEcsactRunnerStarter.generated.h"

UCLASS()

class ECSACTUNREALFPS_API UFloppybotsEcsactRunnerStarter : public UObject {
	GENERATED_BODY() // NOLINT

public:
	UFUNCTION(
		BlueprintCallable,
		Category = "Ecsact Example",
		Meta = (WorldContext = "WorldContext")
	)
	static void StartSingleplayerRunner(UObject* WorldContext);

	UFUNCTION(
		BlueprintCallable,
		Category = "Ecsact Example",
		Meta = (WorldContext = "WorldContext")
	)
	static void StartMultiplayerRunner(UObject* WorldContext);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "Ecsact Example",
		Meta = (WorldContext = "WorldContext")
	)
	static bool IsSingleplayerRunner(UObject* WorldContext);
};
