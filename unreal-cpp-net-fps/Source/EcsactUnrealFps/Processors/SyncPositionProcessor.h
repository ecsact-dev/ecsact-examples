#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "SyncPositionProcessor.generated.h"

UCLASS()

class ECSACTUNREALFPS_API USyncPositionProcessor : public UMassProcessor {
	GENERATED_BODY() // nolint

protected:
	USyncPositionProcessor();

	auto ConfigureQueries() -> void override;
	auto Execute(
		FMassEntityManager&    EntityManager,
		FMassExecutionContext& Context
	) -> void override;

	FMassEntityQuery EntityQuery;
};
