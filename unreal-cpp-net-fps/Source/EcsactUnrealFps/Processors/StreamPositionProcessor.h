#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "StreamPositionProcessor.generated.h"

UCLASS()

class ECSACTUNREALFPS_API UStreamPositionProcessor : public UMassProcessor {
	GENERATED_BODY() // nolint

protected:
	UStreamPositionProcessor();

	auto ConfigureQueries() -> void override;
	auto Execute(
		FMassEntityManager&    EntityManager,
		FMassExecutionContext& Context
	) -> void override;

	FMassEntityQuery EntityQuery;
};
