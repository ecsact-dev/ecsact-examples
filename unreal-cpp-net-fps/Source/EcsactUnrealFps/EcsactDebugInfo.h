#pragma once

#include "CoreMinimal.h"
#include "EcsactDebugInfo.generated.h"

UCLASS()

class ECSACTUNREALFPS_API UEcsactDebugInfo : public UObject {
	GENERATED_BODY()
public:
	/**
	 * Get the tick of the current async runner (if there is one)
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "Ecsact Net Unreal Example",
		Meta = (WorldContext = "WorldContext")
	)
	static int GetAsyncTick(const UObject* WorldContext);
};
