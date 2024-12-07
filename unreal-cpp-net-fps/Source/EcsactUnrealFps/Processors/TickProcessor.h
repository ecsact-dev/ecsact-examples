#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "TickProcessor.generated.h"

UCLASS()

// TODO(Kelwan): Rename this class, it's not clear what it does. Move some logic
// to other processes
class ECSACTUNREALFPS_API UTickProcessor : public UMassProcessor {
	GENERATED_BODY() // nolint

protected:
	UTickProcessor();
	virtual void ConfigureQueries() override;
	virtual void Execute(
		FMassEntityManager&    EntityManager,
		FMassExecutionContext& Context
	) override;

	FMassEntityQuery EntityQuery;
};
