#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "SyncRotationProcessor.generated.h"

UCLASS()

class ECSACTUNREALFPS_API USyncRotationProcessor : public UMassProcessor {
	GENERATED_BODY() // nolint

protected:
	USyncRotationProcessor();

	auto ConfigureQueries() -> void override;
	auto Execute(
		FMassEntityManager&    EntityManager,
		FMassExecutionContext& Context
	) -> void override;

	FMassEntityQuery EntityQuery;
};
