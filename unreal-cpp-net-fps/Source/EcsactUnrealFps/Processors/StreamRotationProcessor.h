#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "StreamRotationProcessor.generated.h"

UCLASS()

class ECSACTUNREALFPS_API UStreamRotationProcessor : public UMassProcessor {
	GENERATED_BODY() // nolint

protected:
	UStreamRotationProcessor();

	auto ConfigureQueries() -> void override;
	auto Execute(
		FMassEntityManager&    EntityManager,
		FMassExecutionContext& Context
	) -> void override;

	FMassEntityQuery EntityQuery;
};
