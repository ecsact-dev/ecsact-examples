#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "EnemyStateTreeProcessor.generated.h"

UCLASS()

class ECSACTUNREALFPS_API UEnemyStateTreeProcessor : public UMassProcessor {
	GENERATED_BODY() // nolint

protected:
	UEnemyStateTreeProcessor();

	auto ConfigureQueries() -> void override;
	auto Execute(
		FMassEntityManager&    EntityManager,
		FMassExecutionContext& Context
	) -> void override;

	FMassEntityQuery EntityQuery;
};
