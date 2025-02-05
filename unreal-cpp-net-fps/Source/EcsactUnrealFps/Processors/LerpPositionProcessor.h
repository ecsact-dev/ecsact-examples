#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "LerpPositionProcessor.generated.h"

UCLASS()

class FLOPPYBOTS_API ULerpPositionProcessor : public UMassProcessor {
	GENERATED_BODY() // nolint

protected:
	ULerpPositionProcessor();

	auto ConfigureQueries() -> void override;
	auto Execute(
		FMassEntityManager&    EntityManager,
		FMassExecutionContext& Context
	) -> void override;

	FMassEntityQuery EntityQuery;
};
