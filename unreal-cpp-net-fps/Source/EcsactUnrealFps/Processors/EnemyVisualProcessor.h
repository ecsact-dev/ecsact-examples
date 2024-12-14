#pragma once

#include "MassRepresentationProcessor.h"
#include "MassVisualizationLODProcessor.h"
#include "EnemyVisualProcessor.generated.h"

UCLASS()

class ECSACTUNREALFPS_API UEnemyVisualProcessor
	: public UMassVisualizationLODProcessor {
	GENERATED_BODY() // nolint

public:
	UEnemyVisualProcessor();

protected:
	auto ConfigureQueries() -> void override;
};

UCLASS()

class ECSACTUNREALFPS_API UEnemyRepresentationProcessor
	: public UMassRepresentationProcessor {
	GENERATED_BODY() // nolint

protected:
	auto ConfigureQueries() -> void override;
};
