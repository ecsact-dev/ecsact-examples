#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "TickProcessor.generated.h"

UCLASS()

class ECSACTUNREALFPS_API UTickProcessor : public UMassProcessor {
	GENERATED_BODY() // nolint

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(
		FMassEntityManager&    EntityManager,
		FMassExecutionContext& Context
	) override;

	FMassEntityQuery EntityQuery;
};
