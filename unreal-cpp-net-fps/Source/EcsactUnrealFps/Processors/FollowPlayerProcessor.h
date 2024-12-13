#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "FollowPlayerProcessor.generated.h"

UCLASS()

class ECSACTUNREALFPS_API UFollowPlayerProcessor : public UMassProcessor {
	GENERATED_BODY() // nolint

protected:
	UFollowPlayerProcessor();

	auto ConfigureQueries() -> void override;
	auto Execute(
		FMassEntityManager&    EntityManager,
		FMassExecutionContext& Context
	) -> void override;

	FMassEntityQuery EntityQuery;
};
