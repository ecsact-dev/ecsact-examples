
#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "EcsactPositionReadProcessor.generated.h"

UCLASS()

// TODO(Kelwan): We shouldn't check an `if` statement in the Tick Processor.
// When the condition is changed, a different processor should run for whether a
// streamed entity is streaming or reading from Ecsact.
class ECSACTUNREALFPS_API UEcsactPositionReadProcessor : public UMassProcessor {
	GENERATED_BODY() // nolint

protected:
	UEcsactPositionReadProcessor();
	virtual void ConfigureQueries() override;
	virtual void Execute(
		FMassEntityManager&    EntityManager,
		FMassExecutionContext& Context
	) override;

	FMassEntityQuery EntityQuery;
};
